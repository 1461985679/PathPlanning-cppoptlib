#pragma once

#include "GeneralHeaders.h" // 引用通用头文件
using namespace std; // 使用标准命名空间

// 定义一个ScoringMethod的类，用于实现划线法
class ScoringMethod {
    private:
    public: // 公开所有的方法

        // 把两点链接，判断是直线链接还是曲线链接
        // 直线连接用bresenham算法，曲线链接用定曲率行走算法 link point to point
        vector<S_PointXY> linkP2P(S_PointXY p0, S_PointXY p1);
        vector<S_PointXY> linkP2P(double x0, double y0, double psi0, double x1, double y1, double psi1);

        // 两点中间经过的直线栅格点 Bresenham算法
        vector<S_PointXY> linkP2P_DirectPart(S_PointXY p0, S_PointXY p1);
        vector<S_PointXY> linkP2P_DirectPart(double x0, double y0, double psi0, double x1, double y1, double psi1);

        // 定曲率的曲线划线法  
        vector<S_PointXY> linkP2P_RoverPart(S_PointXY p0, S_PointXY p1);
        vector<S_PointXY> linkP2P_RoverPart(double x0, double y0, double psi0, double x1, double y1, double psi1);
};

