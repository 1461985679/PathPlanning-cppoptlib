#pragma once // ָʾ������ֻ�Ը��ļ�����һ�α���

#include<iostream>
using namespace std;

// ����һ����Ľṹ�壬����x, y, psi��������
struct S_PointXY
{
    double X;
    double Y;
    double Psi;
    void see();
    bool operator == (const S_PointXY& n)const;
};