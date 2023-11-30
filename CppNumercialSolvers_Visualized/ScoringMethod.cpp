#pragma once

#include"GeneralHeaders.h"
#include "ScoringMethod.h" // ����ͷ�ļ�
#include <vector> // ����������
#include <queue>
using namespace std; // ʹ�ñ�׼�����ռ�

// scoring method ���߷�



// ���������ӣ��ж���ֱ�����ӻ�����������
// ֱ��������bresenham�㷨�����������ö����������㷨 link point to point
vector<S_PointXY> ScoringMethod::linkP2P(S_PointXY p0, S_PointXY p1) {
    return move(linkP2P(p0.X, p0.Y, p0.Psi, p1.X, p1.Y, p1.Psi));
}
vector<S_PointXY> ScoringMethod::linkP2P(double x0, double y0, double psi0, double x1, double y1, double psi1) {
    vector<S_PointXY> track;

    double ePsi1, ePosp0p1;
    double Psip0p1;

    Psip0p1 = atan2(y1 - y0, x1 - x0);
    ePsi1 = ModPI(Psip0p1 - psi0);
    ePosp0p1 = sqrt(SQUARE_SUM(y1 - y0, x1 - x0));

    double Ctr1[2];

    double Disp1C1;

    //ֱ��
    if (fabs(ePsi1) < 2.0 * PI / 32766.0) {
        if (ePosp0p1 > 0.01) {
            psi1 = Psip0p1;
        }
        cerr << "\nstright 1" << endl;;
        return move(linkP2P_DirectPart(x0, y0, psi0, x1, y1, psi1));
    }

    Ctr1[0] = x0 - sin(psi0) * 2 * Sign(ePsi1);
    Ctr1[1] = y0 + cos(psi0) * 2 * Sign(ePsi1);

    Disp1C1 = sqrt(SQUARE_SUM(y1 - Ctr1[1], x1 - Ctr1[0]));
    if (Disp1C1 < 2 || fabs(fabs(ePsi1) - PI) < 0.1) {
        psi1 = Psip0p1;
        cerr << "\nstright 2" << endl;;
        return move(linkP2P_DirectPart(x0, y0, psi0, x1, y1, psi1));
    }


    double Radius = fabs(ePosp0p1 / 2 / sin(ePsi1));



    vector<S_PointXY>roverTrack = linkP2P_RoverPart(x0, y0, psi0, x1, y1, psi1);



    // �ѻ���ӳ��Ϊ����
    for (int i = 0; i < roverTrack.size(); i++) {
        roverTrack[i].X = round(roverTrack[i].X);
        roverTrack[i].Y = round(roverTrack[i].Y);
    }

    

    // һ�������� ������unique���ж���ȥ���Ժ�ķ���ֵ����ɾ������Ľڵ�
    vector<S_PointXY>::iterator iter = unique(roverTrack.begin(), roverTrack.end(), isPositionEqual);
    roverTrack.erase(iter, roverTrack.end());

    // ����ĩβ����
    psi1 = ModPI(psi0 + ePsi1 * 2);
    roverTrack.back().Psi = psi1;
    // ��������
    return move(roverTrack);
}
// �����м侭����ֱ��դ��� Bresenham�㷨
vector<S_PointXY> ScoringMethod::linkP2P_DirectPart(S_PointXY p0, S_PointXY p1) {
    return move(linkP2P_DirectPart(p0.X, p0.Y, p0.Psi, p1.X, p1.Y, p1.Psi));
}
vector<S_PointXY> ScoringMethod::linkP2P_DirectPart(double x0, double y0, double psi0, double x1, double y1, double psi1) {
    // ��ʼ������
    vector<S_PointXY> directTrack;

    // �����Ȼ�������������ҳ�һЩ����Ľ��
    x0 = int(x0); y0 = int(y0);
    x1 = int(x1); y1 = int(y1);
    double dx = abs(x1 - x0); // x����ľ���
    double dy = abs(y1 - y0); // y����ľ���
    double stepx = (x0 < x1) ? 1 : -1; // x����Ĳ���
    double stepy = (y0 < y1) ? 1 : -1; // y����Ĳ���
    double offset = dx - dy; // ���
    double xp = x0; // ��ǰ��x����
    double yp = y0; // ��ǰ��y����

    // ѭ��ֱ�������յ�
    while (true) {
        // �ۼӵ�ǰդ���Ȩֵ
        directTrack.push_back({ double(xp),double(yp),psi0 });
        // ��������յ㣬�˳�ѭ��
        if (xp == x1 && yp == y1) break;
        //if (xp < 0 || yp < 0 || xp >= grid.size() || yp >= grid.size()) {
        //    cerr << "-\n";
        //    cout << "(" << x0 << "," << y0 << ")," << psi0;
        //    cout << "(" << x1 << "," << y1 << "),";
        //    cerr << "ֱ�����ӷ������߽�" << endl;
        //    break;
        //}
        // ������һ��դ�������
        int offset_ = 2 * offset;
        if (offset_ > -dy) {
            offset -= dy;
            xp += stepx;
        }
        if (offset_ < dx) {
            offset += dx;
            yp += stepy;
        }
    }
    directTrack.back().Psi = psi1;
    // ����Ȩֵ֮��   
    return move(directTrack);
}

// �����ʻ��߷�  ���ﻹ��Ҫ��ϸ����
vector<S_PointXY> ScoringMethod::linkP2P_RoverPart(S_PointXY p0, S_PointXY p1) {
    // move���Խ�ʡ�ڴ��ʱ�䣬ֱ���ƶ����points�����Ǹ��������ÿ��Ԫ��
    return move(linkP2P_RoverPart(p0.X, p0.Y, p0.Psi, p1.X, p1.Y, p1.Psi));
}
vector<S_PointXY> ScoringMethod::linkP2P_RoverPart(double x0, double y0, double psi0, double x1, double y1, double psi1) {


    vector<S_PointXY> roverTrack;// ���ߵ㼯

    double PsiTmp;
    double PosTmp[2];
    S_PointXY tmp;


    double Psip0p1 = atan2(y1 - y0, x1 - x0);
    double ePsi1 = ModPI(Psip0p1 - psi0);
    double ePosp0p1 = sqrt(SQUARE_SUM(y1 - y0, x1 - x0));
    double radius = fabs(ePosp0p1 / 2 / sin(ePsi1));

    PosTmp[0] = x0;
    PosTmp[1] = y0;
    PsiTmp = psi0;

    tmp.X = PosTmp[0];
    tmp.Y = PosTmp[1];
    tmp.Psi = PsiTmp;

    double dis_cur = 1 / radius * Sign(ePsi1);
    double dis_length = fabs(ePsi1) * radius * 2;
    double dis_flag = true;

    unsigned int j, StepNum;
    double PsiNext;

    dis_length = fabs(dis_length);
    // ��㾫�� StepNum = ��ĵ������-1  ��Ϊ����Ѿ���ѹ����
    // ������ֱ�߾��� * 3��������� ���Ի�����֤���������е�
    StepNum = static_cast<unsigned int>(int(EuclideanDistance(x0, y0, x1, y1) * 3));
    if (fabs(dis_cur) < 1e-5) {
        for (size_t k = 0; k < StepNum; ++k) {
            if (dis_flag) {
                PosTmp[0] += dis_length * cos(PsiTmp) / StepNum;
                PosTmp[1] += dis_length * sin(PsiTmp) / StepNum;
            }
            else {
                PosTmp[0] -= dis_length * cos(PsiTmp) / StepNum;
                PosTmp[1] -= dis_length * sin(PsiTmp) / StepNum;
            }
            roverTrack.push_back({ PosTmp[0],PosTmp[1],PsiTmp });
        }

    }
    else {
        StepNum = max(static_cast<unsigned int>(StepNum), static_cast<unsigned int>(fabs(dis_length * dis_cur) / 2));
        for (j = 0; j < StepNum; ++j) {
            PsiNext = PsiTmp + dis_length * dis_cur / StepNum;
            if (dis_flag) {
                PosTmp[0] -= (sin(PsiTmp) - sin(PsiNext)) / dis_cur;
                PosTmp[1] += (cos(PsiTmp) - cos(PsiNext)) / dis_cur;
            }
            else {
                PosTmp[0] += (sin(PsiTmp) - sin(PsiNext)) / dis_cur;
                PosTmp[1] -= (cos(PsiTmp) - cos(PsiNext)) / dis_cur;
            }
            PsiTmp = PsiNext;
            roverTrack.push_back({ PosTmp[0],PosTmp[1],PsiTmp });
        }
    }
    roverTrack.push_back({ x1,y1,PsiTmp });


    return move(roverTrack);
}

