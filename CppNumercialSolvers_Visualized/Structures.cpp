// S_PointXY.cpp
#include "GeneralHeaders.h" // ����ͷ�ļ�

// ʵ��see��������������ṹ�������
void S_PointXY::see() {
    cout << "(" << X << "," << Y << "),";
}

// ʵ�����ص�==����������ڱȽ������ṹ���Ƿ����
bool S_PointXY::operator==(const S_PointXY& n) const {
    if (X != n.X) return false;
    if (Y != n.Y) return false;
    if (Psi != n.Psi) return false;
    return true;
}
