#pragma once // ָʾ������ֻ�Ը��ļ�����һ�α���

#include<cmath>
#include<vector>
#include"Structures.h"
using namespace std;

// �������ĺ���

// ƽ����
double SQUARE_SUM(double a, double b);
// ���ź���
double Sign(double a);
// �ѽǶȱ任��[-Pi,Pi]
double ModPI(double theta);
// ŷ�Ͼ���
double EuclideanDistance(S_PointXY pos0, S_PointXY pos1);
// ŷ�Ͼ���
double EuclideanDistance(double x0, double y0, double x1, double y1);
// �㼯��ŷʽ����
double EuclideanDistance(const vector<S_PointXY>& pathPoints);
// unique��Ҫ��ȹ������ж��Ƿ���� 
bool isPositionEqual(S_PointXY a, S_PointXY b);
