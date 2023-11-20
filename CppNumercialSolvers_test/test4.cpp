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
//    const vector<vector<double> > grid;// 栅格地图
//
//    GridPathPlanning(const vector<vector<double> > &grid_) :grid(grid_),
//        Superclass(2){}
//
//    // 欧氏距离
//    double EuclideanDistance(pair<double, double> pos0, pair<double, double> pos1) {
//        return EuclideanDistance(pos0.first, pos0.second, pos1.first, pos1.second);
//    }
//    double EuclideanDistance(double x0, double y0, double x1, double y1) {
//        return pow(x0 - x1, 2) + pow(y0 - y1, 2) + 1;// 距离至少为1 否则重复点就没权值了
//    }
//    // 两点中间经过的地图权值之和 Bresenham算法
//    // 计算从(x0, y0)到(x1, y1)的路径上的栅格的权值之和
//    double LinkGridValue(pair<int, int> pos0, pair<int, int> pos1) {
//        return LinkGridValue(pos0.first, pos0.second, pos1.first, pos1.second);
//    }
//    double LinkGridValue(int x0, int y0, int x1, int y1) {
//        // 初始化变量
//        int dx = abs(x1 - x0); // x方向的距离
//        int dy = abs(y1 - y0); // y方向的距离
//        int stepx = (x0 < x1) ? 1 : -1; // x方向的步长
//        int stepy = (y0 < y1) ? 1 : -1; // y方向的步长
//        int offset = dx - dy; // 误差
//        int xp = x0; // 当前的x坐标
//        int yp = y0; // 当前的y坐标
//        double sum = 0; // 权值之和
//
//        // 循环直到到达终点
//        while (true) {
//            // 累加当前栅格的权值
//			sum += grid[xp][yp];
//            // 如果到达终点，退出循环
//            if (xp == x1 && yp == y1) break;
//            // 计算下一个栅格的坐标
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
//        // 返回权值之和
//        return sum;
//    }
//
//    // this is just the objective (NOT optional)
//    T value(const TVector& x) {
//        
//        
//
//        // 把起点和终点加上中间点合起来
//        vector<pair<int, int> > points = { {sx,sy} };
//        for (int i = 0; i < x.size(); i+=2) {
//            points.push_back({ x[i],x[i + 1] });
//        }
//        points.push_back({ ex,ey });
//        
//        // loss = 两两点之间的(欧氏距离 * 两点中间经过的地图权值)之和
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
//// 简单的两点找单个中间点,在栅格地图上 添加限制 0 <= (x,y) <=9
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
//        Eigen::VectorXd x(2); // 修改x的维数 2代表着x0,y0 一个中间点
//        x.fill(3);
//
//        // 设置边界约束
//        Eigen::VectorXd lb(2);// 下界
//        Eigen::VectorXd ub(2);// 上界
//        lb << 0, 0;
//        ub << grid.size() - 1, grid.size() - 1;
//        // ub << numeric_limits<double>::infinity(), numeric_limits<double>::infinity();
//        f.setBoxConstraint(lb, ub);
//
//        cout << "\n[" << x[0] << "," << x[1] << "] to ";
//        LbfgsbSolver<GridPathPlanning<double> > solver;
//        solver.minimize(f, x); // 只传入x这个参数
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
