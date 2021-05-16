#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include "stdio.h"
#include "math.h"


double function_sin_cos(std::vector<double> start_cond, double x) {
    double prev_sin = start_cond[0], arg_sin = start_cond[1], prev_cos = start_cond[2], arg_cos = start_cond[3];

    return prev_sin * sin(arg_sin * x) + prev_cos * cos(arg_cos * x);
}

double ArgMaxEl(std::vector<double> a) {
    double max = a[0];
    int k = 0;
    int i = 1;
    while (i < a.size()) {
        if (a[i] > max) {
            max = a[i];
            k = i;
        }
        i++;
    }
    return k;
}

std::vector<double> GlobalSearch(double(*function)(std::vector<double>, double), double a, double b,
    double r, double eps, int N_iter, std::vector<double> start_cond, std::vector<double>& graphics) {
    std::vector <std::pair<double, double>> exp;
    std::vector <double> R;
    double M = 0;
    double m;
    std::pair<double, double> p1(a, function(start_cond, a));
    std::pair<double, double> p2(b, function(start_cond, b));
    exp.insert(exp.begin(), p1);
    exp.push_back(p2);
    graphics.push_back(a);
    graphics.push_back(b);
    int k = 2;
    double t = 0;
    while (abs(exp[t + 1].first - exp[t].first) > eps&& k < N_iter) {
        for (int i = 0; i < k - 1; i++) {
            double tmpM = abs((exp[i + 1].second - exp[i].second) / (exp[i + 1].first - exp[i].first));
            if (M < tmpM) M = tmpM;
        }
        if (M == 0) m = 1;
        else m = r * M;
        for (int i = 0; i < k - 1; i++)
            R.push_back(m * (exp[i + 1].first - exp[i].first) + ((exp[i + 1].second - exp[i].second) * (exp[i + 1].second - exp[i].second)) / (m * (exp[i + 1].first - exp[i].first)) - 2 * (exp[i + 1].second + exp[i].second));
        t = ArgMaxEl(R);
        R.clear();
        double c = (exp[t + 1].first + exp[t].first) / 2 - (exp[t + 1].second - exp[t].second) / (2 * m);
        std::pair<double, double> p(c, function(start_cond, c));
        exp.push_back(p);
        graphics.push_back(c);
        sort(exp.begin(), exp.end());
        k++;
    }

    std::vector<double> res(3);
    res[0] = exp[t].second;
    res[1] = exp[t].first;
    res[2] = k;
    return res;
}

std::vector<double> scan(double(*function)(std::vector<double>, double), double a, double b,
    double r, double eps, int N_iter, std::vector<double> start_cond, std::vector<double>& graphics) {
    std::vector <std::pair<double, double>> exp;
    std::vector <double> R;
    double M = 0;
    double m;
    std::pair<double, double> p1(a, function(start_cond, a));
    std::pair<double, double> p2(b, function(start_cond, b));
    exp.insert(exp.begin(), p1);
    exp.push_back(p2);
    graphics.push_back(a);
    graphics.push_back(b);
    std::pair<double, double> min = p1;
    if (min.second > p2.second) min = p2;
    int k = 2;
    double t = 0;
    while (abs(exp[t + 1].first - exp[t].first) > eps&& k < N_iter) {
        for (int i = 0; i < k - 1; i++)
            R.push_back(exp[i + 1].first - exp[i].first);
        t = ArgMaxEl(R);
        R.clear();
        double c = (exp[t + 1].first + exp[t].first) / 2;
        std::pair<double, double> p(c, function(start_cond, c));
        if (p.second < min.second) min = p;
        exp.push_back(p);
        graphics.push_back(c);
        sort(exp.begin(), exp.end());
        k++;
    }

    std::vector<double> res(3);
    res[0] = min.second;
    res[1] = min.first;
    res[2] = k;
    return res;
}

std::vector<double> piyav(double(*function)(std::vector<double>, double), double a, double b,
    double r, double eps, int N_iter, std::vector<double> start_cond, std::vector<double>& graphics) {
    std::vector <std::pair<double, double>> exp;
    std::vector <double> R;
    double M = 0;
    double m;
    std::pair<double, double> p1(a, function(start_cond, a));
    std::pair<double, double> p2(b, function(start_cond, b));
    exp.insert(exp.begin(), p1);
    exp.push_back(p2);
    graphics.push_back(a);
    graphics.push_back(b);
    int k = 2;
    double t = 0;
    while (abs(exp[t + 1].first - exp[t].first) > eps&& k < N_iter) {
        for (int i = 0; i < k - 1; i++) {
            double tmpM = abs((exp[i + 1].second - exp[i].second) / (exp[i + 1].first - exp[i].first));
            if (M < tmpM)
                M = tmpM;
        }
        if (M == 0) m = 1;
        else m = r * M;
        for (int i = 0; i < k - 1; i++) {
            R.push_back(m * (exp[i + 1].first - exp[i].first) / 2 - (exp[i + 1].second + exp[i].second) / 2);
        }
        t = ArgMaxEl(R);
        R.clear();
        double c = (exp[t + 1].first + exp[t].first) / 2 - (exp[t + 1].second - exp[t].second) / (2 * m);
        std::pair<double, double> p(c, function(start_cond, c));
        exp.push_back(p);
        graphics.push_back(c);
        sort(exp.begin(), exp.end());
        k++;
    }

    std::vector<double> res(3);
    res[0] = exp[t].second;
    res[1] = exp[t].first;
    res[2] = k;
    return res;
}

namespace SSSP {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Windows::Forms::DataVisualization;
    using namespace System::Data;
    using namespace System::Drawing;

    public ref class MyForm : public System::Windows::Forms::Form {
    public:
        MyForm(void) {
            InitializeComponent();
        }

    protected:
        ~MyForm() {
            if (components)
                delete components;
        }
    private: System::Windows::Forms::Label^ label1;
    protected:
    private: System::Windows::Forms::Label^ label2;
    private: System::Windows::Forms::NumericUpDown^ prev_sin;

    private: System::Windows::Forms::Label^ label3;
    private: System::Windows::Forms::NumericUpDown^ arg_sin;

    private: System::Windows::Forms::Label^ label4;
    private: System::Windows::Forms::Label^ label5;
    private: System::Windows::Forms::NumericUpDown^ prev_cos;

    private: System::Windows::Forms::Label^ label6;
    private: System::Windows::Forms::NumericUpDown^ arg_cos;

    private: System::Windows::Forms::Label^ label7;
    private: System::Windows::Forms::Label^ label8;
    private: System::Windows::Forms::Label^ label9;
    private: System::Windows::Forms::Label^ label10;
    private: System::Windows::Forms::NumericUpDown^ left_border;

    private: System::Windows::Forms::Label^ label11;
    private: System::Windows::Forms::NumericUpDown^ right_border;

    private: System::Windows::Forms::Label^ label12;
    private: System::Windows::Forms::RadioButton^ Strongin;
    private: System::Windows::Forms::RadioButton^ Piyavskiy;
    private: System::Windows::Forms::RadioButton^ enumeration;

    private: System::Windows::Forms::Label^ label13;
    private: System::Windows::Forms::NumericUpDown^ r;

    private: System::Windows::Forms::Label^ label14;
    private: System::Windows::Forms::NumericUpDown^ eps;

    private: System::Windows::Forms::Label^ label15;
    private: System::Windows::Forms::NumericUpDown^ max_iter;

    private: System::Windows::Forms::Button^ button1;
    private: System::Windows::Forms::Label^ label16;
    private: System::Windows::Forms::Label^ label17;
    private: System::Windows::Forms::Label^ label18;
    private: System::Windows::Forms::TextBox^ min;
    private: System::Windows::Forms::TextBox^ iter;

    private: System::Windows::Forms::TextBox^ coordinate;
    private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;

    private:
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void) {
            System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
            System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
            System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
            System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
            System::Windows::Forms::DataVisualization::Charting::Series^ series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->prev_sin = (gcnew System::Windows::Forms::NumericUpDown());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->arg_sin = (gcnew System::Windows::Forms::NumericUpDown());
            this->label4 = (gcnew System::Windows::Forms::Label());
            this->label5 = (gcnew System::Windows::Forms::Label());
            this->prev_cos = (gcnew System::Windows::Forms::NumericUpDown());
            this->label6 = (gcnew System::Windows::Forms::Label());
            this->arg_cos = (gcnew System::Windows::Forms::NumericUpDown());
            this->label7 = (gcnew System::Windows::Forms::Label());
            this->label8 = (gcnew System::Windows::Forms::Label());
            this->label9 = (gcnew System::Windows::Forms::Label());
            this->label10 = (gcnew System::Windows::Forms::Label());
            this->left_border = (gcnew System::Windows::Forms::NumericUpDown());
            this->label11 = (gcnew System::Windows::Forms::Label());
            this->right_border = (gcnew System::Windows::Forms::NumericUpDown());
            this->label12 = (gcnew System::Windows::Forms::Label());
            this->Strongin = (gcnew System::Windows::Forms::RadioButton());
            this->Piyavskiy = (gcnew System::Windows::Forms::RadioButton());
            this->enumeration = (gcnew System::Windows::Forms::RadioButton());
            this->label13 = (gcnew System::Windows::Forms::Label());
            this->r = (gcnew System::Windows::Forms::NumericUpDown());
            this->label14 = (gcnew System::Windows::Forms::Label());
            this->eps = (gcnew System::Windows::Forms::NumericUpDown());
            this->label15 = (gcnew System::Windows::Forms::Label());
            this->max_iter = (gcnew System::Windows::Forms::NumericUpDown());
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->label16 = (gcnew System::Windows::Forms::Label());
            this->label17 = (gcnew System::Windows::Forms::Label());
            this->label18 = (gcnew System::Windows::Forms::Label());
            this->min = (gcnew System::Windows::Forms::TextBox());
            this->iter = (gcnew System::Windows::Forms::TextBox());
            this->coordinate = (gcnew System::Windows::Forms::TextBox());
            this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->prev_sin))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->arg_sin))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->prev_cos))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->arg_cos))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->left_border))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->right_border))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->r))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->eps))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->max_iter))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
            this->SuspendLayout();
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label1->Location = System::Drawing::Point(19, 9);
            this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(318, 24);
            this->label1->TabIndex = 0;
            this->label1->Text = L"Поиск глобального минимума F(x)";
            // 
            // label2
            // 
            this->label2->AutoSize = true;
            this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label2->Location = System::Drawing::Point(22, 89);
            this->label2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(65, 24);
            this->label2->TabIndex = 1;
            this->label2->Text = L"F(x)  =";
            // 
            // prev_sin
            // 
            this->prev_sin->DecimalPlaces = 2;
            this->prev_sin->Location = System::Drawing::Point(98, 94);
            this->prev_sin->Margin = System::Windows::Forms::Padding(2);
            this->prev_sin->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
            this->prev_sin->Name = L"prev_sin";
            this->prev_sin->Size = System::Drawing::Size(46, 20);
            this->prev_sin->TabIndex = 2;
            this->prev_sin->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label3->Location = System::Drawing::Point(145, 89);
            this->label3->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(37, 24);
            this->label3->TabIndex = 3;
            this->label3->Text = L"Sin";
            // 
            // arg_sin
            // 
            this->arg_sin->DecimalPlaces = 2;
            this->arg_sin->Location = System::Drawing::Point(186, 94);
            this->arg_sin->Margin = System::Windows::Forms::Padding(2);
            this->arg_sin->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
            this->arg_sin->Name = L"arg_sin";
            this->arg_sin->Size = System::Drawing::Size(42, 20);
            this->arg_sin->TabIndex = 4;
            this->arg_sin->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3, 0, 0, 0 });
            // 
            // label4
            // 
            this->label4->AutoSize = true;
            this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label4->Location = System::Drawing::Point(232, 89);
            this->label4->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
            this->label4->Name = L"label4";
            this->label4->Size = System::Drawing::Size(20, 24);
            this->label4->TabIndex = 5;
            this->label4->Text = L"x";
            // 
            // label5
            // 
            this->label5->AutoSize = true;
            this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label5->Location = System::Drawing::Point(256, 89);
            this->label5->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
            this->label5->Name = L"label5";
            this->label5->Size = System::Drawing::Size(21, 24);
            this->label5->TabIndex = 6;
            this->label5->Text = L"+";
            // 
            // prev_cos
            // 
            this->prev_cos->DecimalPlaces = 2;
            this->prev_cos->Location = System::Drawing::Point(281, 93);
            this->prev_cos->Margin = System::Windows::Forms::Padding(2);
            this->prev_cos->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
            this->prev_cos->Name = L"prev_cos";
            this->prev_cos->Size = System::Drawing::Size(46, 20);
            this->prev_cos->TabIndex = 7;
            this->prev_cos->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 3, 0, 0, System::Int32::MinValue });
            // 
            // label6
            // 
            this->label6->AutoSize = true;
            this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label6->Location = System::Drawing::Point(331, 89);
            this->label6->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
            this->label6->Name = L"label6";
            this->label6->Size = System::Drawing::Size(43, 24);
            this->label6->TabIndex = 8;
            this->label6->Text = L"Cos";
            // 
            // arg_cos
            // 
            this->arg_cos->DecimalPlaces = 2;
            this->arg_cos->Location = System::Drawing::Point(378, 94);
            this->arg_cos->Margin = System::Windows::Forms::Padding(2);
            this->arg_cos->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
            this->arg_cos->Name = L"arg_cos";
            this->arg_cos->Size = System::Drawing::Size(46, 20);
            this->arg_cos->TabIndex = 9;
            this->arg_cos->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, System::Int32::MinValue });
            // 
            // label7
            // 
            this->label7->AutoSize = true;
            this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label7->Location = System::Drawing::Point(430, 89);
            this->label7->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
            this->label7->Name = L"label7";
            this->label7->Size = System::Drawing::Size(20, 24);
            this->label7->TabIndex = 10;
            this->label7->Text = L"x";
            // 
            // label8
            // 
            this->label8->AutoSize = true;
            this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label8->Location = System::Drawing::Point(25, 131);
            this->label8->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
            this->label8->Name = L"label8";
            this->label8->Size = System::Drawing::Size(24, 24);
            this->label8->TabIndex = 11;
            this->label8->Text = L"X";
            // 
            // label9
            // 
            this->label9->AutoSize = true;
            this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 19.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label9->Location = System::Drawing::Point(42, 124);
            this->label9->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
            this->label9->Name = L"label9";
            this->label9->Size = System::Drawing::Size(30, 31);
            this->label9->TabIndex = 12;
            this->label9->Text = L"∈";
            // 
            // label10
            // 
            this->label10->AutoSize = true;
            this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label10->Location = System::Drawing::Point(68, 129);
            this->label10->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
            this->label10->Name = L"label10";
            this->label10->Size = System::Drawing::Size(19, 26);
            this->label10->TabIndex = 13;
            this->label10->Text = L"{";
            // 
            // left_border
            // 
            this->left_border->DecimalPlaces = 1;
            this->left_border->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
            this->left_border->Location = System::Drawing::Point(84, 135);
            this->left_border->Margin = System::Windows::Forms::Padding(2);
            this->left_border->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
            this->left_border->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, System::Int32::MinValue });
            this->left_border->Name = L"left_border";
            this->left_border->Size = System::Drawing::Size(46, 20);
            this->left_border->TabIndex = 14;
            this->left_border->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, System::Int32::MinValue });
            // 
            // label11
            // 
            this->label11->AutoSize = true;
            this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label11->Location = System::Drawing::Point(135, 128);
            this->label11->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
            this->label11->Name = L"label11";
            this->label11->Size = System::Drawing::Size(18, 26);
            this->label11->TabIndex = 15;
            this->label11->Text = L";";
            // 
            // right_border
            // 
            this->right_border->DecimalPlaces = 1;
            this->right_border->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
            this->right_border->Location = System::Drawing::Point(157, 135);
            this->right_border->Margin = System::Windows::Forms::Padding(2);
            this->right_border->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
            this->right_border->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, System::Int32::MinValue });
            this->right_border->Name = L"right_border";
            this->right_border->Size = System::Drawing::Size(46, 20);
            this->right_border->TabIndex = 16;
            this->right_border->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
            // 
            // label12
            // 
            this->label12->AutoSize = true;
            this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label12->Location = System::Drawing::Point(202, 131);
            this->label12->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
            this->label12->Name = L"label12";
            this->label12->Size = System::Drawing::Size(19, 26);
            this->label12->TabIndex = 17;
            this->label12->Text = L"}";
            // 
            // Strongin
            // 
            this->Strongin->AutoSize = true;
            this->Strongin->Checked = true;
            this->Strongin->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->Strongin->Location = System::Drawing::Point(23, 48);
            this->Strongin->Margin = System::Windows::Forms::Padding(2);
            this->Strongin->Name = L"Strongin";
            this->Strongin->Size = System::Drawing::Size(99, 24);
            this->Strongin->TabIndex = 18;
            this->Strongin->TabStop = true;
            this->Strongin->Text = L"Стронгин";
            this->Strongin->UseVisualStyleBackColor = true;
            // 
            // Piyavskiy
            // 
            this->Piyavskiy->AutoSize = true;
            this->Piyavskiy->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->Piyavskiy->Location = System::Drawing::Point(126, 48);
            this->Piyavskiy->Margin = System::Windows::Forms::Padding(2);
            this->Piyavskiy->Name = L"Piyavskiy";
            this->Piyavskiy->Size = System::Drawing::Size(100, 24);
            this->Piyavskiy->TabIndex = 19;
            this->Piyavskiy->TabStop = true;
            this->Piyavskiy->Text = L"Пиявский";
            this->Piyavskiy->UseVisualStyleBackColor = true;
            // 
            // enumeration
            // 
            this->enumeration->AutoSize = true;
            this->enumeration->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->enumeration->Location = System::Drawing::Point(234, 48);
            this->enumeration->Margin = System::Windows::Forms::Padding(2);
            this->enumeration->Name = L"enumeration";
            this->enumeration->Size = System::Drawing::Size(93, 24);
            this->enumeration->TabIndex = 20;
            this->enumeration->TabStop = true;
            this->enumeration->Text = L"Перебор";
            this->enumeration->UseVisualStyleBackColor = true;
            // 
            // label13
            // 
            this->label13->AutoSize = true;
            this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label13->Location = System::Drawing::Point(25, 180);
            this->label13->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
            this->label13->Name = L"label13";
            this->label13->Size = System::Drawing::Size(157, 20);
            this->label13->TabIndex = 21;
            this->label13->Text = L"Параметр метода r";
            // 
            // r
            // 
            this->r->DecimalPlaces = 1;
            this->r->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
            this->r->Location = System::Drawing::Point(346, 180);
            this->r->Margin = System::Windows::Forms::Padding(2);
            this->r->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
            this->r->Name = L"r";
            this->r->Size = System::Drawing::Size(90, 20);
            this->r->TabIndex = 22;
            this->r->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 15, 0, 0, 65536 });
            // 
            // label14
            // 
            this->label14->AutoSize = true;
            this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label14->Location = System::Drawing::Point(25, 202);
            this->label14->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
            this->label14->Name = L"label14";
            this->label14->Size = System::Drawing::Size(205, 20);
            this->label14->TabIndex = 23;
            this->label14->Text = L"Допустимая погрешность";
            // 
            // eps
            // 
            this->eps->DecimalPlaces = 5;
            this->eps->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 262144 });
            this->eps->Location = System::Drawing::Point(346, 205);
            this->eps->Margin = System::Windows::Forms::Padding(2);
            this->eps->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100, 0, 0, System::Int32::MinValue });
            this->eps->Name = L"eps";
            this->eps->Size = System::Drawing::Size(90, 20);
            this->eps->TabIndex = 24;
            this->eps->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 262144 });
            // 
            // label15
            // 
            this->label15->AutoSize = true;
            this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label15->Location = System::Drawing::Point(25, 227);
            this->label15->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
            this->label15->Name = L"label15";
            this->label15->Size = System::Drawing::Size(317, 20);
            this->label15->TabIndex = 25;
            this->label15->Text = L"Максимальное допустимое число шагов";
            // 
            // max_iter
            // 
            this->max_iter->Location = System::Drawing::Point(346, 230);
            this->max_iter->Margin = System::Windows::Forms::Padding(2);
            this->max_iter->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
            this->max_iter->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
            this->max_iter->Name = L"max_iter";
            this->max_iter->Size = System::Drawing::Size(90, 20);
            this->max_iter->TabIndex = 26;
            this->max_iter->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
            // 
            // button1
            // 
            this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->button1->Location = System::Drawing::Point(23, 385);
            this->button1->Margin = System::Windows::Forms::Padding(2);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(413, 46);
            this->button1->TabIndex = 27;
            this->button1->Text = L"Расчёт";
            this->button1->UseVisualStyleBackColor = true;
            this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
            // 
            // label16
            // 
            this->label16->AutoSize = true;
            this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label16->Location = System::Drawing::Point(19, 446);
            this->label16->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
            this->label16->Name = L"label16";
            this->label16->Size = System::Drawing::Size(168, 20);
            this->label16->TabIndex = 28;
            this->label16->Text = L"Найденный минимум";
            // 
            // label17
            // 
            this->label17->AutoSize = true;
            this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label17->Location = System::Drawing::Point(19, 474);
            this->label17->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
            this->label17->Name = L"label17";
            this->label17->Size = System::Drawing::Size(190, 20);
            this->label17->TabIndex = 29;
            this->label17->Text = L"Найденная координата";
            // 
            // label18
            // 
            this->label18->AutoSize = true;
            this->label18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label18->Location = System::Drawing::Point(19, 504);
            this->label18->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
            this->label18->Name = L"label18";
            this->label18->Size = System::Drawing::Size(238, 20);
            this->label18->TabIndex = 30;
            this->label18->Text = L"Число проведённых итераций";
            // 
            // min
            // 
            this->min->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->min->Location = System::Drawing::Point(261, 446);
            this->min->Margin = System::Windows::Forms::Padding(2);
            this->min->Name = L"min";
            this->min->Size = System::Drawing::Size(114, 26);
            this->min->TabIndex = 31;
            // 
            // iter
            // 
            this->iter->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->iter->Location = System::Drawing::Point(261, 504);
            this->iter->Margin = System::Windows::Forms::Padding(2);
            this->iter->Name = L"iter";
            this->iter->Size = System::Drawing::Size(114, 26);
            this->iter->TabIndex = 32;
            // 
            // coordinate
            // 
            this->coordinate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->coordinate->Location = System::Drawing::Point(261, 475);
            this->coordinate->Margin = System::Windows::Forms::Padding(2);
            this->coordinate->Name = L"coordinate";
            this->coordinate->Size = System::Drawing::Size(114, 26);
            this->coordinate->TabIndex = 33;
            // 
            // chart1
            // 
            chartArea1->Name = L"ChartArea1";
            this->chart1->ChartAreas->Add(chartArea1);
            legend1->Name = L"Legend1";
            this->chart1->Legends->Add(legend1);
            this->chart1->Location = System::Drawing::Point(486, 11);
            this->chart1->Margin = System::Windows::Forms::Padding(2);
            this->chart1->Name = L"chart1";
            series1->BorderWidth = 3;
            series1->ChartArea = L"ChartArea1";
            series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
            series1->Legend = L"Legend1";
            series1->MarkerSize = 7;
            series1->Name = L"Траектория";
            series2->ChartArea = L"ChartArea1";
            series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
            series2->Color = System::Drawing::Color::Red;
            series2->Legend = L"Legend1";
            series2->MarkerBorderWidth = 2;
            series2->MarkerSize = 8;
            series2->Name = L"Точки испытания";
            series2->YValuesPerPoint = 2;
            series3->ChartArea = L"ChartArea1";
            series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
            series3->Legend = L"Legend1";
            series3->MarkerColor = System::Drawing::Color::Lime;
            series3->Name = L"Результат";
            series3->YValuesPerPoint = 2;
            this->chart1->Series->Add(series1);
            this->chart1->Series->Add(series2);
            this->chart1->Series->Add(series3);
            this->chart1->Size = System::Drawing::Size(605, 514);
            this->chart1->TabIndex = 34;
            this->chart1->Text = L"chart1";
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->AutoSize = true;
            this->ClientSize = System::Drawing::Size(1102, 539);
            this->Controls->Add(this->chart1);
            this->Controls->Add(this->coordinate);
            this->Controls->Add(this->iter);
            this->Controls->Add(this->min);
            this->Controls->Add(this->label18);
            this->Controls->Add(this->label17);
            this->Controls->Add(this->label16);
            this->Controls->Add(this->button1);
            this->Controls->Add(this->max_iter);
            this->Controls->Add(this->label15);
            this->Controls->Add(this->eps);
            this->Controls->Add(this->label14);
            this->Controls->Add(this->r);
            this->Controls->Add(this->label13);
            this->Controls->Add(this->enumeration);
            this->Controls->Add(this->Piyavskiy);
            this->Controls->Add(this->Strongin);
            this->Controls->Add(this->label12);
            this->Controls->Add(this->right_border);
            this->Controls->Add(this->label11);
            this->Controls->Add(this->left_border);
            this->Controls->Add(this->label10);
            this->Controls->Add(this->label9);
            this->Controls->Add(this->label8);
            this->Controls->Add(this->label7);
            this->Controls->Add(this->arg_cos);
            this->Controls->Add(this->label6);
            this->Controls->Add(this->prev_cos);
            this->Controls->Add(this->label5);
            this->Controls->Add(this->label4);
            this->Controls->Add(this->arg_sin);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->prev_sin);
            this->Controls->Add(this->label2);
            this->Controls->Add(this->label1);
            this->Margin = System::Windows::Forms::Padding(2);
            this->Name = L"MyForm";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"Поиск глобального минимума | Смирнов Александр 381803-2";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->prev_sin))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->arg_sin))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->prev_cos))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->arg_cos))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->left_border))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->right_border))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->r))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->eps))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->max_iter))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
    private: System::Void SSSP::MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e) {
        std::vector<double> first_con = { Convert::ToDouble(prev_sin->Value), Convert::ToDouble(arg_sin->Value),
            Convert::ToDouble(prev_cos->Value), Convert::ToDouble(arg_cos->Value) };
        double a = Convert::ToDouble(left_border->Value);
        double b = Convert::ToDouble(right_border->Value);
        double(*ptr)(std::vector<double>, double) = function_sin_cos;
        double rp = Convert::ToDouble(r->Value);
        double epsilon = Convert::ToDouble(eps->Value);
        int N = Convert::ToInt32(max_iter->Value);

        if (Strongin->Checked) {
            std::vector<double> graph;
            std::vector<double> res = GlobalSearch(ptr, a, b, rp, epsilon, N, first_con, graph);
            min->Text = Convert::ToString(res[0]);
            coordinate->Text = Convert::ToString(res[1]);
            iter->Text = Convert::ToString(res[2]);
            chart1->Series[0]->Points->Clear();
            chart1->Series[1]->Points->Clear();
            chart1->Series[2]->Points->Clear();
            double x = a, h = 0.01, y;
            while (x <= b) {
                y = function_sin_cos(first_con, x);
                chart1->Series[0]->Points->AddXY(x, y);
                x += h;
            }

            for (int i = 0; i < graph.size(); i++)
                chart1->Series[2]->Points->AddXY(graph[i], res[0] - 2);

            chart1->Series[1]->Points->AddXY(res[1], res[0]);
        }

        if (enumeration->Checked) {
            std::vector<double> graph;
            std::vector<double> res = scan(ptr, a, b, rp, epsilon, N, first_con, graph);
            min->Text = Convert::ToString(res[0]);
            coordinate->Text = Convert::ToString(res[1]);
            iter->Text = Convert::ToString(res[2]);
            chart1->Series[0]->Points->Clear();
            chart1->Series[1]->Points->Clear();
            chart1->Series[2]->Points->Clear();
            double x = a, h = 0.01, y;
            while (x <= b) {
                y = function_sin_cos(first_con, x);
                chart1->Series[0]->Points->AddXY(x, y);
                x += h;
            }

            for (int i = 0; i < graph.size(); i++)
                chart1->Series[2]->Points->AddXY(graph[i], res[0] - 2);

            chart1->Series[1]->Points->AddXY(res[1], res[0]);
        }

        if (Piyavskiy->Checked) {
            std::vector<double> graph;
            std::vector<double> res = piyav(ptr, a, b, rp, epsilon, N, first_con, graph);
            min->Text = Convert::ToString(res[0]);
            coordinate->Text = Convert::ToString(res[1]);
            iter->Text = Convert::ToString(res[2]);
            chart1->Series[0]->Points->Clear();
            chart1->Series[1]->Points->Clear();
            chart1->Series[2]->Points->Clear();
            double x = a, h = 0.01, y;
            while (x <= b) {
                y = function_sin_cos(first_con, x);
                chart1->Series[0]->Points->AddXY(x, y);
                x += h;
            }

            for (int i = 0; i < graph.size(); i++)
                chart1->Series[2]->Points->AddXY(graph[i], res[0] - 2);

            chart1->Series[1]->Points->AddXY(res[1], res[0]);
        }

        return System::Void();
    };
    };
}

