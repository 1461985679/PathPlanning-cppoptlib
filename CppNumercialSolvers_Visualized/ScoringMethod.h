#pragma once

#include "GeneralHeaders.h" // ����ͨ��ͷ�ļ�
using namespace std; // ʹ�ñ�׼�����ռ�

// ����һ��ScoringMethod���࣬����ʵ�ֻ��߷�
class ScoringMethod {
    private:
    public: // �������еķ���

        // ���������ӣ��ж���ֱ�����ӻ�����������
        // ֱ��������bresenham�㷨�����������ö����������㷨 link point to point
        vector<S_PointXY> linkP2P(S_PointXY p0, S_PointXY p1);
        vector<S_PointXY> linkP2P(double x0, double y0, double psi0, double x1, double y1, double psi1);

        // �����м侭����ֱ��դ��� Bresenham�㷨
        vector<S_PointXY> linkP2P_DirectPart(S_PointXY p0, S_PointXY p1);
        vector<S_PointXY> linkP2P_DirectPart(double x0, double y0, double psi0, double x1, double y1, double psi1);

        // �����ʵ����߻��߷�  
        vector<S_PointXY> linkP2P_RoverPart(S_PointXY p0, S_PointXY p1);
        vector<S_PointXY> linkP2P_RoverPart(double x0, double y0, double psi0, double x1, double y1, double psi1);
};

