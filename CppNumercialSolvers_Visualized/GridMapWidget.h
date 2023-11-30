#include <QPainter> // 引用Qt的绘图类
#include <QWidget> // 引用Qt的窗口类
#include <QLineEdit>
#include <QPushButton>
#include"Structures.h"
// 定义一个GridMapWidget的类，继承自QWidget
class GridMapWidget : public QWidget {
    Q_OBJECT // Qt的宏，用于支持信号和槽等特性

public:
    // 构造函数
    GridMapWidget(int windowWidth, int windowHeight, int mapWidth,int mapHeight,QWidget* parent = nullptr);

    // 重写paintEvent函数，用于绘制窗口的内容
    void paintEvent(QPaintEvent* event) override;

private slots:
    // 处理显示按钮的点击事件
    void onShowButtonClicked();

private:

    // 实现绘制坐标轴的函数
    void GridMapWidget::paintAxis(QPainter& painter);

   

    // 计算合适的刻度间隔的函数，参数是轴的长度
    int calculateTickSize(int length);

    // 定义一个绘制箭头的函数，接受一个QPainter对象的引用，一个S_PointXY(方向有效)，一个箭头的大小作为参数
    void drawArrow(QPainter& painter, S_PointXY point, int arrowSize);
    // 定义一个绘制箭头的函数，接受一个QPainter对象的引用，一个点的坐标和方向，一个箭头的大小作为参数
    void drawArrow(QPainter& painter, int x, int y, double psi, int arrowSize);
    // 定义一个绘制箭头的函数，接受一个QPainter对象的引用，两个S_PointXY(方向无效)，一个箭头的大小作为参数
    void drawArrow(QPainter& painter, S_PointXY start,S_PointXY end, int arrowSize);
    // 定义一个绘制箭头的函数，接受一个QPainter对象的引用，两个点的坐标，一个箭头的大小作为参数
    void drawArrow(QPainter& painter, int sx, int sy, int ex, int ey, int arrowSize);

    // 其他的成员变量
    QLineEdit* sxEdit; // 起点x坐标的输入框
    QLineEdit* syEdit; // 起点y坐标的输入框
    QLineEdit* spsiEdit; // 起点角度的输入框
    QLineEdit* exEdit; // 终点x坐标的输入框
    QLineEdit* eyEdit; // 终点y坐标的输入框
    QLineEdit* epsiEdit; // 终点角度的输入框
    QPushButton* showButton; // 显示按钮
    QTransform transform; // 变换矩阵
    QString mapFile; // 栅格地图的文件名
    S_PointXY start; // 起点
    S_PointXY end; // 终点
    int mapWidth,mapHeight;// 地图长宽
    // 坐标偏移量 因为默认是左上角原点的坐标，得改成左下角方便显示
    // 为了确保坐标不会二次偏移，请仅仅在painter.XXX的地方改填偏移量
    int offsetX, offsetY; 
    QVector<S_PointXY> points; // 点集
};