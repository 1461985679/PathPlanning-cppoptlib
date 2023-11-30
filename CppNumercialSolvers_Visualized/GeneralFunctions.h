#pragma once // 指示编译器只对该文件进行一次编译

#include<cmath>
#include<vector>
#include"Structures.h"
using namespace std;

// 声明您的函数

// 平方和
double SQUARE_SUM(double a, double b);
// 符号函数
double Sign(double a);
// 把角度变换到[-Pi,Pi]
double ModPI(double theta);
// 欧氏距离
double EuclideanDistance(S_PointXY pos0, S_PointXY pos1);
// 欧氏距离
double EuclideanDistance(double x0, double y0, double x1, double y1);
// 点集的欧式距离
double EuclideanDistance(const vector<S_PointXY>& pathPoints);
// unique需要相等规则来判断是否相等 
bool isPositionEqual(S_PointXY a, S_PointXY b);
