//#include<bits/stdc++.h>
//#include<cppoptlib/meta.h>
//#include<cppoptlib/problem.h>
//#include<cppoptlib/solver/bfgssolver.h>
//
//// nolintnextline
//using namespace cppoptlib;
//using namespace std;
//
//
//
//double sx, sy, ex, ey;
//int num;
//
//// we define a new problem for optimizing the Simple function
//// we use a templated-class rather than "auto"-lambda function for a clean architecture
//template<typename T>
//class Simple : public Problem<T> {
//public:
//    using typename Problem<T>::TVector;
//
//    double EuclideanDistance(double x1, double y1, double x2, double y2) {
//        return pow(x1 - x2, 2) + pow(y1 - y2, 2);
//    }
//    // this is just the objective (NOT optional)
//    T value(const TVector& p) {
//        double sumDis = 0;
//        //起点到第一个中间点
//        sumDis += EuclideanDistance(sx, sy, p[0], p[1]);
//        //最后的中间点到终点
//        sumDis += EuclideanDistance(p[p.size() - 2], p[p.size() - 1], ex, ey);
//        //中间点之间
//        for (int i = 2; i < p.size(); i += 2) {
//            sumDis += EuclideanDistance(p[i - 2], p[i - 1], p[i], p[i + 1]);
//        }
//
//        return sumDis;
//    }
//};
////复杂一些的，两点找n个中间点 欧氏距离的
//int main(int argc, char const* argv[]) {
//
//    int  _(999);
//    while (_--) {
//        cout << "g me 2 pos:" << endl;
//        cin >> sx >> sy >> ex >> ey;
//        cout << "g me 1 num:" << endl;
//
//        cin >> num;
//
//        Simple<double> f;
//        Eigen::VectorXd path((num - 2) * 2);
//        path.fill(1);
//        cout << "1" << endl;
//        BfgsSolver<Simple<double>> solver;
//        solver.minimize(f, path);
//
//        for (int i = 0; i < path.size(); i += 2) {
//            cout << "[" << path[i] << "," << path[i + 1] << "]  ";
//        }
//
//
//
//        cout << "f in argmin " << f(path) << endl;
//        cout << "Solver status: " << solver.status() << endl;
//        cout << "Final criteria values: " << endl << solver.criteria() << endl;
//    }
//    return 0;
//}
