//#include <iostream>
//#include <vector>
//#include <cmath>
//#include <cppoptlib/meta.h>
//#include <cppoptlib/solver/lbfgsbsolver.h>
//#include <cppoptlib/boundedproblem.h>
//
//// nolintnextline
//using namespace cppoptlib;
//using namespace std;
//
//
//int sx, sy, ex, ey;
//int num;
//
//
//template<typename T>
//class GridPathPlanning : public BoundedProblem<T> {
//public:
//    using Superclass = BoundedProblem<T>;
//    using typename Superclass::TVector;
//    using TMatrix = typename Superclass::THessian;
//
//
//    const vector<vector<double> > grid;// դ���ͼ
//
//    GridPathPlanning(const vector<vector<double> > &grid_) :grid(grid_),
//        Superclass(2){}
//
//    // ŷ�Ͼ���
//    double EuclideanDistance(pair<double, double> pos0, pair<double, double> pos1) {
//        return EuclideanDistance(pos0.first, pos0.second, pos1.first, pos1.second);
//    }
//    double EuclideanDistance(double x0, double y0, double x1, double y1) {
//        return pow(x0 - x1, 2) + pow(y0 - y1, 2) + 1;// ��������Ϊ1 �����ظ����ûȨֵ��
//    }
//    // �����м侭���ĵ�ͼȨֵ֮�� Bresenham�㷨
//    // �����(x0, y0)��(x1, y1)��·���ϵ�դ���Ȩֵ֮��
//    double LinkGridValue(pair<int, int> pos0, pair<int, int> pos1) {
//        return LinkGridValue(pos0.first, pos0.second, pos1.first, pos1.second);
//    }
//    double LinkGridValue(int x0, int y0, int x1, int y1) {
//        // ��ʼ������
//        int dx = abs(x1 - x0); // x����ľ���
//        int dy = abs(y1 - y0); // y����ľ���
//        int stepx = (x0 < x1) ? 1 : -1; // x����Ĳ���
//        int stepy = (y0 < y1) ? 1 : -1; // y����Ĳ���
//        int offset = dx - dy; // ���
//        int xp = x0; // ��ǰ��x����
//        int yp = y0; // ��ǰ��y����
//        double sum = 0; // Ȩֵ֮��
//
//        // ѭ��ֱ�������յ�
//        while (true) {
//            // �ۼӵ�ǰդ���Ȩֵ
//			sum += grid[xp][yp];
//            // ��������յ㣬�˳�ѭ��
//            if (xp == x1 && yp == y1) break;
//            // ������һ��դ�������
//            int offset_ = 2 * offset;
//            if (offset_ > -dy) {
//                offset -= dy;
//                xp += stepx;
//            }
//            if (offset_ < dx) {
//                offset += dx;
//                yp += stepy;
//            }
//        }
//        // ����Ȩֵ֮��
//        return sum;
//    }
//
//    // this is just the objective (NOT optional)
//    T value(const TVector& x) {
//        
//        
//
//        // �������յ�����м�������
//        vector<pair<int, int> > points = { {sx,sy} };
//        for (int i = 0; i < x.size(); i+=2) {
//            points.push_back({ x[i],x[i + 1] });
//        }
//        points.push_back({ ex,ey });
//        
//        // loss = ������֮���(ŷ�Ͼ��� * �����м侭���ĵ�ͼȨֵ)֮��
//        double sumValue = 0;
//        for (int i = 0; i < points.size() - 1; i++) {
//            sumValue += EuclideanDistance(points[i], points[i + 1]) * LinkGridValue(points[i], points[i + 1]);
//        }
//
//        cout << "[";
//        for (int i = 0; i < points.size(); i++) {
//            if (i)cout << ",";
//            cout << "[" << points[i].first << "," << points[i].second << "]";
//        }
//        cout << "]\n";
//        //cout << sumValue << ",,,\n";
//        return move(sumValue);
//    }
//};
//// �򵥵������ҵ����м��,��դ���ͼ�� ������� 0 <= (x,y) <=9
//int main(int argc, char const* argv[]) {
//    const vector<vector<double> > grid = {
//    {0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
//    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//    {1, 1, 1, 0, 0, 1, 1, 1, 1, 0},
//    {4, 4, 4, 4, 2, 2, 4, 4, 2, 1},
//    {1, 1, 1, 1, 1, 1, 1, 3, 1, 1},
//    {0, 0, 0, 0, 0, 1, 0, 0, 1, 3},
//    {1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
//    {2, 2, 2, 2, 2, 2, 2, 2, 1, 3},
//    {3, 3, 3, 3, 3, 3, 3, 0, 0, 3},
//    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
//    };
//
//    GridPathPlanning<double> f(grid);
//    int _ = 999;
//    while (_--) {
//        cout << "g me 2 pos:\n";
//        cin >> sx >> sy >> ex >> ey;
//
//        GridPathPlanning<double> f(grid);
//        Eigen::VectorXd x(2); // �޸�x��ά�� 2������x0,y0 һ���м��
//        x.fill(3);
//
//        // ���ñ߽�Լ��
//        Eigen::VectorXd lb(2);// �½�
//        Eigen::VectorXd ub(2);// �Ͻ�
//        lb << 0, 0;
//        ub << grid.size() - 1, grid.size() - 1;
//        // ub << numeric_limits<double>::infinity(), numeric_limits<double>::infinity();
//        f.setBoxConstraint(lb, ub);
//
//        cout << "\n[" << x[0] << "," << x[1] << "] to ";
//        LbfgsbSolver<GridPathPlanning<double> > solver;
//        solver.minimize(f, x); // ֻ����x�������
//        cout << "[" << (int)x[0] << "," << (int)x[1] << "]\n" << endl;
//
//
//        cout << "f in argmin " << f(x) << endl;
//        cout << "Solver status: " << solver.status() << endl;
//        cout << "Final criteria values: " << endl << solver.criteria() << endl;
//
//
//    }
//    return 0;
//}
