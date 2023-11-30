#pragma once // 指示编译器只对该文件进行一次编译

#include<iostream>
using namespace std;

// 定义一个点的结构体，包含x, y, psi三个属性
struct S_PointXY
{
    double X;
    double Y;
    double Psi;
    void see();
    bool operator == (const S_PointXY& n)const;
};