#include "GridMapWidget.h" // ����ͷ�ļ�
#include <QPainter>
#include <QImage>
#include <cmath>
#include "GeneralHeaders.h"
#include "ScoringMethod.h"

// ʵ�ֹ��캯��
GridMapWidget::GridMapWidget(int windowWidth, int windowHeight,int mapWidth,int mapHeight, QWidget* parent)
    :  mapWidth(mapWidth), mapHeight(mapHeight) {
    
    offsetX = offsetY = 400;


    // ���ô��ڵı���ʹ�С
    setWindowTitle("Grid Map");
    setFixedSize(windowWidth, windowHeight);
    // ��ʼ���任����
    transform = QTransform(); // ����һ���任����
    // ��ʼ�������Ͱ�ť

    sxEdit = new QLineEdit(this); // �������x����������
    sxEdit->setGeometry(10, 10, 100, 30); // ����������λ�úʹ�С
    sxEdit->setPlaceholderText("sx"); // ������������ʾ����
    sxEdit->setText("0");// Ĭ��ֵ
    
    syEdit = new QLineEdit(this); // �������y����������
    syEdit->setGeometry(120, 10, 100, 30); // ����������λ�úʹ�С
    syEdit->setPlaceholderText("sy"); // ������������ʾ����
    syEdit->setText("0");// Ĭ��ֵ

    spsiEdit = new QLineEdit(this); // �������Ƕȵ������
    spsiEdit->setGeometry(230, 10, 100, 30); // ����������λ�úʹ�С
    spsiEdit->setPlaceholderText("spsi"); // ������������ʾ����
    spsiEdit->setText("0");// Ĭ��ֵ

    exEdit = new QLineEdit(this); // �����յ�x����������
    exEdit->setGeometry(340, 10, 100, 30); // ����������λ�úʹ�С
    exEdit->setPlaceholderText("ex"); // ������������ʾ����
    exEdit->setText("200");// Ĭ��ֵ

    eyEdit = new QLineEdit(this); // �����յ�y����������
    eyEdit->setGeometry(450, 10, 100, 30); // ����������λ�úʹ�С
    eyEdit->setPlaceholderText("ey"); // ������������ʾ����
    eyEdit->setText("300");// Ĭ��ֵ

    epsiEdit = new QLineEdit(this); // �����յ�Ƕȵ������
    epsiEdit->setGeometry(560, 10, 100, 30); // ����������λ�úʹ�С
    epsiEdit->setPlaceholderText("epsi"); // ������������ʾ����
    epsiEdit->setText("0");// Ĭ��ֵ

    showButton = new QPushButton(this); // ������ʾ��ť
    showButton->setGeometry(670, 10, 100, 30); // ���ð�ť��λ�úʹ�С
    showButton->setText("��ʾ"); // ���ð�ť������
    // ���Ӱ�ť�ĵ���źźͲۺ���
    connect(showButton, SIGNAL(clicked()), this, SLOT(onShowButtonClicked()));
}

// ʵ�ֲۺ���
void GridMapWidget::onShowButtonClicked() {
    // ��������л�ȡ�û����������
    double sx = sxEdit->text().toDouble();
    double sy = syEdit->text().toDouble();
    double spsi = spsiEdit->text().toDouble();
    double ex = exEdit->text().toDouble();
    double ey = eyEdit->text().toDouble();
    double epsi = epsiEdit->text().toDouble();
    // ���������յ�Ľṹ��
    S_PointXY sp = { sx, sy, spsi };
    S_PointXY ep = { ex, ey, epsi };
    // ����һ������������(�������
    ScoringMethod pencil;
    // ����һ���㼯���û��߷���������ת��QVector
    QVector<S_PointXY> points = QVector<S_PointXY>::fromStdVector(pencil.linkP2P(sp, ep));
    // ���³�Ա����
    start = sp;
    end = ep;
    this->points = points;
    // ���»��ƴ���
    update();
}


// ʵ��paintEvent����
void GridMapWidget::paintEvent(QPaintEvent* event) {
    // ����һ��QPainter�������ڻ��ƴ��ڵ�����
    QPainter painter(this);
    //���������
    paintAxis(painter);
}

// ʵ�ֻ���������ĺ���
void GridMapWidget::paintAxis(QPainter& painter){


    // ���û��ʵ���ɫ�Ϳ��
    painter.setPen(QPen(Qt::red, 3));


    // ���û��ʵ���ɫ�Ϳ��
    painter.setPen(QPen(Qt::red, 3));

    // ����x���y�������
    painter.drawLine(offsetX, height() - offsetY, offsetX + mapWidth * 1.2, height() - offsetY); // x��
    painter.drawLine(offsetX, height() - offsetY, offsetX, height() - offsetY - mapHeight * 1.2); // y��

    // ����x���y��Ŀ̶� �̶ȳ�������Ӧ��ͼ
    int tickSize = calculateTickSize(mapWidth);
    // ����x��Ŀ̶�
    for (int x = tickSize; x <= mapWidth; x += tickSize) {
        // ���ƿ̶���
        painter.drawLine(offsetX + x, height() - offsetY - 5, offsetX + x, height() - offsetY + 5);
        // ���ƿ̶�ֵ
        painter.drawText(offsetX + x - 10, height() - offsetY + 20, QString::number(x));

    }
    tickSize = calculateTickSize(mapHeight);
    // ����y��Ŀ̶�
    for (int y = tickSize; y <= mapHeight; y += tickSize) {
        // ���ƿ̶���
        painter.drawLine(offsetX - 5, height() - offsetY - y, offsetX + 5, height() - offsetY - y);
        // ���ƿ̶�ֵ
        painter.drawText(offsetX - 30, height() - offsetY - y, QString::number(y));
    }

    // ���������յ� ����ר�ű�ע�ģ�����ʵpoints����β��������յ�
    painter.drawEllipse(offsetX + start.X - 5, height() - offsetY - start.Y - 5, 10, 10);
    painter.drawEllipse(offsetX + end.X - 5, height() - offsetY - end.Y - 5, 10, 10);

    // �����㼯������ÿ����ͼ�ͷ
    for (int i = 0; i < points.size(); i++) {
        // ��ȡ��ǰ�������ͽǶ�
        int x = points[i].X;
        int y = points[i].Y;
        double psi = points[i].Psi;

        // ���û��ʵ���ɫ�Ϳ��
        painter.setPen(QPen(Qt::blue, 2));
        // ���Ƶ�
        painter.drawEllipse(offsetX + x - 3, height() - offsetY - y - 3, 6, 6);

        // ���Ƽ�ͷ
        if (i % 30 == 0)drawArrow(painter, points[i], 10);
    }
    // ���Ƶ㼯֮�������
    painter.setPen(QPen(Qt::green, 2)); // ���û��ʵ���ɫ�Ϳ��
    for (int i = 0; i < points.size() - 1; i++) {
        // ��ȡ��ǰ�����һ���������
        int x1 = points[i].X;
        int y1 = points[i].Y;
        int x2 = points[i + 1].X;
        int y2 = points[i + 1].Y;
        // ��������
        painter.drawLine(offsetX + x1, height() - offsetY - y1, offsetX + x2, height() - offsetY - y2);
    }

}





// ����һ�����Ƽ�ͷ�ĺ���������һ��QPainter��������ã�һ��S_PointXY(������Ч)��һ����ͷ�Ĵ�С��Ϊ����
void GridMapWidget::drawArrow(QPainter& painter, S_PointXY point, int arrowSize) {
    drawArrow(painter, point.X, point.Y, point.Psi, arrowSize);
}
// ����һ�����Ƽ�ͷ�ĺ���������һ��QPainter��������ã�һ���������ͷ���һ����ͷ�Ĵ�С��Ϊ����
void GridMapWidget::drawArrow(QPainter& painter, int x, int y,double psi, int arrowSize) {
    // �����ͷ���յ������
    int ex = x + 20 * cos(psi);
    int ey = y + 20 * sin(psi);
    drawArrow(painter, x, y, ex, ey, arrowSize);
}
// ����һ�����Ƽ�ͷ�ĺ���������һ��QPainter��������ã�����S_PointXY(������Ч)��һ����ͷ�Ĵ�С��Ϊ����
void GridMapWidget::drawArrow(QPainter& painter, S_PointXY start, S_PointXY end, int arrowSize) {
    drawArrow(painter, start.X, start.Y, end.X, end.Y, arrowSize);
}
// ����һ�����Ƽ�ͷ�ĺ���������һ��QPainter��������ã�����������꣬һ����ͷ�Ĵ�С��Ϊ����
void GridMapWidget::drawArrow(QPainter& painter, int sx, int sy,int ex,int ey, int arrowSize) {
    // ���û��ʵ���ɫ�Ϳ��
    painter.setPen(QPen(Qt::black, 2));
    // ����ֱ�ߵĳ��ȺͽǶ�
    double length = sqrt((ex - sx) * (ex - sx) + (ey - sy) * (ey - sy));
    // �޸ĽǶȵļ��㷽ʽ��ʹ����y��������Ϊ0��˳ʱ�����ӣ���ʱ�����
    double angle = atan2(ex - sx, sy - ey);

    // �����ͷ�������˵������
    // �޸�����ļ��㷽ʽ��ʹ����Ƕȱ���һ��
    int arrowsx = ex - arrowSize * sin(angle - PI / 4); 
    int arrowsy = ey + arrowSize * cos(angle - PI / 4); 
    int arrowex = ex - arrowSize * sin(angle + PI / 4); 
    int arrowey = ey + arrowSize * cos(angle + PI / 4); 

    // ���Ƽ�ͷ�������˵�
    // ������ͷ�Ļ���˳���Ȼ��Ƽ�ͷ�������˵㣬�ٻ���ֱ��
    painter.drawLine(offsetX + ex, height() - offsetY - ey, offsetX + arrowsx, height() - offsetY - arrowsy);
    painter.drawLine(offsetX + ex, height() - offsetY - ey, offsetX + arrowex, height() - offsetY - arrowey);

    // ����ֱ��
    painter.drawLine(offsetX + sx, height() - offsetY - sy, offsetX + ex, height() - offsetY - ey);

}


// ʵ�ּ�����ʵĿ̶ȼ���ĺ���
int GridMapWidget::calculateTickSize(int length) {
    // ����̶ȼ���ĳ�ʼֵ��1
    int tickSize = 0;
    // �����ĳ��ȴ���10���Ͳ��ϵ����ӿ̶ȼ����ֱ������ֵ�ӽ���ĳ��ȵ�1/10
    while (tickSize < length / 10) tickSize += 10;
    // ���ؿ̶ȼ����ֵ
    return tickSize;
}
