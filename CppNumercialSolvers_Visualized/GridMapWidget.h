#include <QPainter> // ����Qt�Ļ�ͼ��
#include <QWidget> // ����Qt�Ĵ�����
#include <QLineEdit>
#include <QPushButton>
#include"Structures.h"
// ����һ��GridMapWidget���࣬�̳���QWidget
class GridMapWidget : public QWidget {
    Q_OBJECT // Qt�ĺ꣬����֧���źźͲ۵�����

public:
    // ���캯��
    GridMapWidget(int windowWidth, int windowHeight, int mapWidth,int mapHeight,QWidget* parent = nullptr);

    // ��дpaintEvent���������ڻ��ƴ��ڵ�����
    void paintEvent(QPaintEvent* event) override;

private slots:
    // ������ʾ��ť�ĵ���¼�
    void onShowButtonClicked();

private:

    // ʵ�ֻ���������ĺ���
    void GridMapWidget::paintAxis(QPainter& painter);

   

    // ������ʵĿ̶ȼ���ĺ�������������ĳ���
    int calculateTickSize(int length);

    // ����һ�����Ƽ�ͷ�ĺ���������һ��QPainter��������ã�һ��S_PointXY(������Ч)��һ����ͷ�Ĵ�С��Ϊ����
    void drawArrow(QPainter& painter, S_PointXY point, int arrowSize);
    // ����һ�����Ƽ�ͷ�ĺ���������һ��QPainter��������ã�һ���������ͷ���һ����ͷ�Ĵ�С��Ϊ����
    void drawArrow(QPainter& painter, int x, int y, double psi, int arrowSize);
    // ����һ�����Ƽ�ͷ�ĺ���������һ��QPainter��������ã�����S_PointXY(������Ч)��һ����ͷ�Ĵ�С��Ϊ����
    void drawArrow(QPainter& painter, S_PointXY start,S_PointXY end, int arrowSize);
    // ����һ�����Ƽ�ͷ�ĺ���������һ��QPainter��������ã�����������꣬һ����ͷ�Ĵ�С��Ϊ����
    void drawArrow(QPainter& painter, int sx, int sy, int ex, int ey, int arrowSize);

    // �����ĳ�Ա����
    QLineEdit* sxEdit; // ���x����������
    QLineEdit* syEdit; // ���y����������
    QLineEdit* spsiEdit; // ���Ƕȵ������
    QLineEdit* exEdit; // �յ�x����������
    QLineEdit* eyEdit; // �յ�y����������
    QLineEdit* epsiEdit; // �յ�Ƕȵ������
    QPushButton* showButton; // ��ʾ��ť
    QTransform transform; // �任����
    QString mapFile; // դ���ͼ���ļ���
    S_PointXY start; // ���
    S_PointXY end; // �յ�
    int mapWidth,mapHeight;// ��ͼ����
    // ����ƫ���� ��ΪĬ�������Ͻ�ԭ������꣬�øĳ����½Ƿ�����ʾ
    // Ϊ��ȷ�����겻�����ƫ�ƣ��������painter.XXX�ĵط�����ƫ����
    int offsetX, offsetY; 
    QVector<S_PointXY> points; // �㼯
};