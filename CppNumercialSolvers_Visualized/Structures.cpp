// S_PointXY.cpp
#include "GeneralHeaders.h" // 引用头文件

// 实现see函数，用于输出结构体的内容
void S_PointXY::see() {
    cout << "(" << X << "," << Y << "),";
}

// 实现重载的==运算符，用于比较两个结构体是否相等
bool S_PointXY::operator==(const S_PointXY& n) const {
    if (X != n.X) return false;
    if (Y != n.Y) return false;
    if (Psi != n.Psi) return false;
    return true;
}
