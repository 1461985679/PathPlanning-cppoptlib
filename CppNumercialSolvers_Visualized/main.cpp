// main.cpp
#include <QApplication> // ����Qt��Ӧ�ó�����
#include <QWidget> // ����Qt�Ĵ��ڲ�����
#include <QPainter> // ����Qt�Ļ�ͼ��
#include "GridMapWidget.h" // �����Լ������ͷ�ļ�
#include "ScoringMethod.h"


// ����һ��main����
int main(int argc, char* argv[]) {
    // ����һ��QApplication����
    QApplication app(argc, argv);
    // ����һ��GridMapWidget��ʵ����ֻ����դ���ͼ���ļ���
    GridMapWidget widget(800,800,500,500);
    // ��ʾ���ӻ�����
    widget.show();
    // ����Ӧ�ó����ִ��
    return app.exec();
}

