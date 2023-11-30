// GeneralFunctions.cpp
#include "GeneralHeaders.h" // 引用头文件
#include<vector>

using namespace std;
// 平方和
double SQUARE_SUM(double a, double b) {
    return a * a + b * b;
}
// 符号函数
double Sign(double a) {
    return a > 0 ? 1 : -1;
}
// 角度变换到[-pi，pi]之间
double ModPI(double theta) {
    theta = fmod(theta, 2 * PI);
    if (theta > PI)
        theta -= 2.0 * PI;
    else if (theta <= -PI)
        theta += 2.0 * PI;
    return theta;
}

// 欧氏距离
double EuclideanDistance(S_PointXY pos0, S_PointXY pos1) {
    return EuclideanDistance(pos0.X, pos0.Y, pos1.X, pos1.Y);
}
// 欧氏距离
double EuclideanDistance(double x0, double y0, double x1, double y1) {
    return sqrt(pow(x0 - x1, 2) + pow(y0 - y1, 2));
}
// 点集的欧式距离
double fixedCruvatureDistance(const vector<S_PointXY>& pathPoints) {
    double sum = 0;
    for (int i = 0; i < pathPoints.size() - 1; i++) {
        sum += EuclideanDistance(pathPoints[i], pathPoints[i + 1]);
    }
    return sum;
}

// unique需要相等规则来判断是否相等 
bool isPositionEqual(S_PointXY a, S_PointXY b) {

    if (a.X != b.X)return false;
    if (a.Y != b.Y)return false;
    return true;
};