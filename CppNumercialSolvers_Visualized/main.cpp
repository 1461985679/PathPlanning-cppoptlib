// main.cpp
#include <QApplication> // 引用Qt的应用程序类
#include <QWidget> // 引用Qt的窗口部件类
#include <QPainter> // 引用Qt的绘图类
#include "GridMapWidget.h" // 引用自己定义的头文件
#include "ScoringMethod.h"


// 定义一个main函数
int main(int argc, char* argv[]) {
    // 创建一个QApplication对象
    QApplication app(argc, argv);
    // 创建一个GridMapWidget的实例，只传入栅格地图的文件名
    GridMapWidget widget(800,800,500,500);
    // 显示可视化界面
    widget.show();
    // 启动应用程序的执行
    return app.exec();
}

