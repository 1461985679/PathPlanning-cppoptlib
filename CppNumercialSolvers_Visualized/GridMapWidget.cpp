#include "GridMapWidget.h" // 引用头文件
#include <QPainter>
#include <QImage>
#include <cmath>
#include "GeneralHeaders.h"
#include "ScoringMethod.h"

// 实现构造函数
GridMapWidget::GridMapWidget(int windowWidth, int windowHeight,int mapWidth,int mapHeight, QWidget* parent)
    :  mapWidth(mapWidth), mapHeight(mapHeight) {
    
    offsetX = offsetY = 400;


    // 设置窗口的标题和大小
    setWindowTitle("Grid Map");
    setFixedSize(windowWidth, windowHeight);
    // 初始化变换矩阵
    transform = QTransform(); // 创建一个变换矩阵
    // 初始化输入框和按钮

    sxEdit = new QLineEdit(this); // 创建起点x坐标的输入框
    sxEdit->setGeometry(10, 10, 100, 30); // 设置输入框的位置和大小
    sxEdit->setPlaceholderText("sx"); // 设置输入框的提示文字
    sxEdit->setText("0");// 默认值
    
    syEdit = new QLineEdit(this); // 创建起点y坐标的输入框
    syEdit->setGeometry(120, 10, 100, 30); // 设置输入框的位置和大小
    syEdit->setPlaceholderText("sy"); // 设置输入框的提示文字
    syEdit->setText("0");// 默认值

    spsiEdit = new QLineEdit(this); // 创建起点角度的输入框
    spsiEdit->setGeometry(230, 10, 100, 30); // 设置输入框的位置和大小
    spsiEdit->setPlaceholderText("spsi"); // 设置输入框的提示文字
    spsiEdit->setText("0");// 默认值

    exEdit = new QLineEdit(this); // 创建终点x坐标的输入框
    exEdit->setGeometry(340, 10, 100, 30); // 设置输入框的位置和大小
    exEdit->setPlaceholderText("ex"); // 设置输入框的提示文字
    exEdit->setText("200");// 默认值

    eyEdit = new QLineEdit(this); // 创建终点y坐标的输入框
    eyEdit->setGeometry(450, 10, 100, 30); // 设置输入框的位置和大小
    eyEdit->setPlaceholderText("ey"); // 设置输入框的提示文字
    eyEdit->setText("300");// 默认值

    epsiEdit = new QLineEdit(this); // 创建终点角度的输入框
    epsiEdit->setGeometry(560, 10, 100, 30); // 设置输入框的位置和大小
    epsiEdit->setPlaceholderText("epsi"); // 设置输入框的提示文字
    epsiEdit->setText("0");// 默认值

    showButton = new QPushButton(this); // 创建显示按钮
    showButton->setGeometry(670, 10, 100, 30); // 设置按钮的位置和大小
    showButton->setText("显示"); // 设置按钮的文字
    // 连接按钮的点击信号和槽函数
    connect(showButton, SIGNAL(clicked()), this, SLOT(onShowButtonClicked()));
}

// 实现槽函数
void GridMapWidget::onShowButtonClicked() {
    // 从输入框中获取用户输入的数据
    double sx = sxEdit->text().toDouble();
    double sy = syEdit->text().toDouble();
    double spsi = spsiEdit->text().toDouble();
    double ex = exEdit->text().toDouble();
    double ey = eyEdit->text().toDouble();
    double epsi = epsiEdit->text().toDouble();
    // 创建起点和终点的结构体
    S_PointXY sp = { sx, sy, spsi };
    S_PointXY ep = { ex, ey, epsi };
    // 定义一根笔用来划线(很形象吧
    ScoringMethod pencil;
    // 创建一个点集，用划线法划出来并转成QVector
    QVector<S_PointXY> points = QVector<S_PointXY>::fromStdVector(pencil.linkP2P(sp, ep));
    // 更新成员变量
    start = sp;
    end = ep;
    this->points = points;
    // 重新绘制窗口
    update();
}


// 实现paintEvent函数
void GridMapWidget::paintEvent(QPaintEvent* event) {
    // 创建一个QPainter对象，用于绘制窗口的内容
    QPainter painter(this);
    //坐标轴绘制
    paintAxis(painter);
}

// 实现绘制坐标轴的函数
void GridMapWidget::paintAxis(QPainter& painter){


    // 设置画笔的颜色和宽度
    painter.setPen(QPen(Qt::red, 3));


    // 设置画笔的颜色和宽度
    painter.setPen(QPen(Qt::red, 3));

    // 绘制x轴和y轴的线条
    painter.drawLine(offsetX, height() - offsetY, offsetX + mapWidth * 1.2, height() - offsetY); // x轴
    painter.drawLine(offsetX, height() - offsetY, offsetX, height() - offsetY - mapHeight * 1.2); // y轴

    // 绘制x轴和y轴的刻度 刻度长度自适应地图
    int tickSize = calculateTickSize(mapWidth);
    // 遍历x轴的刻度
    for (int x = tickSize; x <= mapWidth; x += tickSize) {
        // 绘制刻度线
        painter.drawLine(offsetX + x, height() - offsetY - 5, offsetX + x, height() - offsetY + 5);
        // 绘制刻度值
        painter.drawText(offsetX + x - 10, height() - offsetY + 20, QString::number(x));

    }
    tickSize = calculateTickSize(mapHeight);
    // 遍历y轴的刻度
    for (int y = tickSize; y <= mapHeight; y += tickSize) {
        // 绘制刻度线
        painter.drawLine(offsetX - 5, height() - offsetY - y, offsetX + 5, height() - offsetY - y);
        // 绘制刻度值
        painter.drawText(offsetX - 30, height() - offsetY - y, QString::number(y));
    }

    // 绘制起点和终点 这是专门标注的，但其实points的首尾就是起点终点
    painter.drawEllipse(offsetX + start.X - 5, height() - offsetY - start.Y - 5, 10, 10);
    painter.drawEllipse(offsetX + end.X - 5, height() - offsetY - end.Y - 5, 10, 10);

    // 遍历点集，绘制每个点和箭头
    for (int i = 0; i < points.size(); i++) {
        // 获取当前点的坐标和角度
        int x = points[i].X;
        int y = points[i].Y;
        double psi = points[i].Psi;

        // 设置画笔的颜色和宽度
        painter.setPen(QPen(Qt::blue, 2));
        // 绘制点
        painter.drawEllipse(offsetX + x - 3, height() - offsetY - y - 3, 6, 6);

        // 绘制箭头
        if (i % 30 == 0)drawArrow(painter, points[i], 10);
    }
    // 绘制点集之间的连线
    painter.setPen(QPen(Qt::green, 2)); // 设置画笔的颜色和宽度
    for (int i = 0; i < points.size() - 1; i++) {
        // 获取当前点和下一个点的坐标
        int x1 = points[i].X;
        int y1 = points[i].Y;
        int x2 = points[i + 1].X;
        int y2 = points[i + 1].Y;
        // 绘制连线
        painter.drawLine(offsetX + x1, height() - offsetY - y1, offsetX + x2, height() - offsetY - y2);
    }

}





// 定义一个绘制箭头的函数，接受一个QPainter对象的引用，一个S_PointXY(方向有效)，一个箭头的大小作为参数
void GridMapWidget::drawArrow(QPainter& painter, S_PointXY point, int arrowSize) {
    drawArrow(painter, point.X, point.Y, point.Psi, arrowSize);
}
// 定义一个绘制箭头的函数，接受一个QPainter对象的引用，一个点的坐标和方向，一个箭头的大小作为参数
void GridMapWidget::drawArrow(QPainter& painter, int x, int y,double psi, int arrowSize) {
    // 计算箭头的终点的坐标
    int ex = x + 20 * cos(psi);
    int ey = y + 20 * sin(psi);
    drawArrow(painter, x, y, ex, ey, arrowSize);
}
// 定义一个绘制箭头的函数，接受一个QPainter对象的引用，两个S_PointXY(方向无效)，一个箭头的大小作为参数
void GridMapWidget::drawArrow(QPainter& painter, S_PointXY start, S_PointXY end, int arrowSize) {
    drawArrow(painter, start.X, start.Y, end.X, end.Y, arrowSize);
}
// 定义一个绘制箭头的函数，接受一个QPainter对象的引用，两个点的坐标，一个箭头的大小作为参数
void GridMapWidget::drawArrow(QPainter& painter, int sx, int sy,int ex,int ey, int arrowSize) {
    // 设置画笔的颜色和宽度
    painter.setPen(QPen(Qt::black, 2));
    // 计算直线的长度和角度
    double length = sqrt((ex - sx) * (ex - sx) + (ey - sy) * (ey - sy));
    // 修改角度的计算方式，使其以y轴正方向为0，顺时针增加，逆时针减少
    double angle = atan2(ex - sx, sy - ey);

    // 计算箭头的两个端点的坐标
    // 修改坐标的计算方式，使其与角度保持一致
    int arrowsx = ex - arrowSize * sin(angle - PI / 4); 
    int arrowsy = ey + arrowSize * cos(angle - PI / 4); 
    int arrowex = ex - arrowSize * sin(angle + PI / 4); 
    int arrowey = ey + arrowSize * cos(angle + PI / 4); 

    // 绘制箭头的两个端点
    // 调换箭头的绘制顺序，先绘制箭头的两个端点，再绘制直线
    painter.drawLine(offsetX + ex, height() - offsetY - ey, offsetX + arrowsx, height() - offsetY - arrowsy);
    painter.drawLine(offsetX + ex, height() - offsetY - ey, offsetX + arrowex, height() - offsetY - arrowey);

    // 绘制直线
    painter.drawLine(offsetX + sx, height() - offsetY - sy, offsetX + ex, height() - offsetY - ey);

}


// 实现计算合适的刻度间隔的函数
int GridMapWidget::calculateTickSize(int length) {
    // 假设刻度间隔的初始值是1
    int tickSize = 0;
    // 如果轴的长度大于10，就不断地增加刻度间隔，直到它的值接近轴的长度的1/10
    while (tickSize < length / 10) tickSize += 10;
    // 返回刻度间隔的值
    return tickSize;
}
