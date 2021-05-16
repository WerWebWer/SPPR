#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include "stdio.h"
#include "math.h"

#include "Form1.h"


//double function_sin_cos(std::vector<double> start_cond, double x) {
//    double prev_sin = start_cond[0], arg_sin = start_cond[1], prev_cos = start_cond[2], arg_cos = start_cond[3];
//
//    return prev_sin * sin(arg_sin * x) + prev_cos * cos(arg_cos * x);
//}
//
//double ArgMaxEl(std::vector<double> a) {
//    double max = a[0];
//    int k = 0;
//    int i = 1;
//    while (i < a.size()) {
//        if (a[i] > max) {
//            max = a[i];
//            k = i;
//        }
//        i++;
//    }
//    return k;
//}
//
//std::vector<double> GlobalSearch(double(*function)(std::vector<double>, double), double a, double b,
//    double r, double eps, int N_iter, std::vector<double> start_cond, std::vector<double>& graphics) {
//    std::vector <std::pair<double, double>> exp;
//    std::vector <double> R;
//    double M = 0;
//    double m;
//    std::pair<double, double> p1(a, function(start_cond, a));
//    std::pair<double, double> p2(b, function(start_cond, b));
//    exp.insert(exp.begin(), p1);
//    exp.push_back(p2);
//    graphics.push_back(a);
//    graphics.push_back(b);
//    int k = 2;
//    double t = 0;
//    while (abs(exp[t + 1].first - exp[t].first) > eps&& k < N_iter) {
//        for (int i = 0; i < k - 1; i++) {
//            double tmpM = abs((exp[i + 1].second - exp[i].second) / (exp[i + 1].first - exp[i].first));
//            if (M < tmpM) M = tmpM;
//        }
//        if (M == 0) m = 1;
//        else m = r * M;
//        for (int i = 0; i < k - 1; i++)
//            R.push_back(m * (exp[i + 1].first - exp[i].first) + ((exp[i + 1].second - exp[i].second) * (exp[i + 1].second - exp[i].second)) / (m * (exp[i + 1].first - exp[i].first)) - 2 * (exp[i + 1].second + exp[i].second));
//        t = ArgMaxEl(R);
//        R.clear();
//        double c = (exp[t + 1].first + exp[t].first) / 2 - (exp[t + 1].second - exp[t].second) / (2 * m);
//        std::pair<double, double> p(c, function(start_cond, c));
//        exp.push_back(p);
//        graphics.push_back(c);
//        sort(exp.begin(), exp.end());
//        k++;
//    }
//
//    std::vector<double> res(3);
//    res[0] = exp[t].second;
//    res[1] = exp[t].first;
//    res[2] = k;
//    return res;
//}
//
//std::vector<double> scan(double(*function)(std::vector<double>, double), double a, double b,
//    double r, double eps, int N_iter, std::vector<double> start_cond, std::vector<double>& graphics) {
//    std::vector <std::pair<double, double>> exp;
//    std::vector <double> R;
//    double M = 0;
//    double m;
//    std::pair<double, double> p1(a, function(start_cond, a));
//    std::pair<double, double> p2(b, function(start_cond, b));
//    exp.insert(exp.begin(), p1);
//    exp.push_back(p2);
//    graphics.push_back(a);
//    graphics.push_back(b);
//    std::pair<double, double> min = p1;
//    if (min.second > p2.second) min = p2;
//    int k = 2;
//    double t = 0;
//    while (abs(exp[t + 1].first - exp[t].first) > eps&& k < N_iter) {
//        for (int i = 0; i < k - 1; i++)
//            R.push_back(exp[i + 1].first - exp[i].first);
//        t = ArgMaxEl(R);
//        R.clear();
//        double c = (exp[t + 1].first + exp[t].first) / 2;
//        std::pair<double, double> p(c, function(start_cond, c));
//        if (p.second < min.second) min = p;
//        exp.push_back(p);
//        graphics.push_back(c);
//        sort(exp.begin(), exp.end());
//        k++;
//    }
//
//    std::vector<double> res(3);
//    res[0] = min.second;
//    res[1] = min.first;
//    res[2] = k;
//    return res;
//}
//
//std::vector<double> piyav(double(*function)(std::vector<double>, double), double a, double b,
//    double r, double eps, int N_iter, std::vector<double> start_cond, std::vector<double>& graphics){
//    std::vector <std::pair<double, double>> exp;
//    std::vector <double> R;
//    double M = 0;
//    double m;
//    std::pair<double, double> p1(a, function(start_cond, a));
//    std::pair<double, double> p2(b, function(start_cond, b));
//    exp.insert(exp.begin(), p1);
//    exp.push_back(p2);
//    graphics.push_back(a);
//    graphics.push_back(b);
//    int k = 2;
//    double t = 0;
//    while (abs(exp[t + 1].first - exp[t].first) > eps&& k < N_iter) {
//        for (int i = 0; i < k - 1; i++) {
//            double tmpM = abs((exp[i + 1].second - exp[i].second) / (exp[i + 1].first - exp[i].first));
//            if (M < tmpM)
//                M = tmpM;
//        }
//        if (M == 0) m = 1;
//        else m = r * M;
//        for (int i = 0; i < k - 1; i++) {
//            R.push_back(m * (exp[i + 1].first - exp[i].first) / 2 - (exp[i + 1].second + exp[i].second) / 2);
//        }
//        t = ArgMaxEl(R);
//        R.clear();
//        double c = (exp[t + 1].first + exp[t].first) / 2 - (exp[t + 1].second - exp[t].second) / (2 * m);
//        std::pair<double, double> p(c, function(start_cond, c));
//        exp.push_back(p);
//        graphics.push_back(c);
//        sort(exp.begin(), exp.end());
//        k++;
//    }
//
//    std::vector<double> res(3);
//    res[0] = exp[t].second;
//    res[1] = exp[t].first;
//    res[2] = k;
//    return res;
//}