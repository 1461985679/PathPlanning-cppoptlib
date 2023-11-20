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
//    T value(const TVector& x) {
//        return EuclideanDistance(sx,sy,x[0],x[1]) + EuclideanDistance(ex, ey, x[0], x[1]);
//    }
//    
//    //// if you calculated the derivative by hand
//    //// you can implement it here (OPTIONAL)
//    //// otherwise it will fall back to (bad) numerical finite differences
//    //void gradient(const TVector& x, TVector& grad) {
//    //    grad[0] = 2 * 5 * x[0];
//    //    grad[1] = 2 * 100 * x[1];
//    //}
//};
////简单的两点找单个中间点
//int main(int argc, char const* argv[]) {
//    int _ = 999;
//    while (_--) {
//        cout << "g me 2 pos:\n";
//        cin >> sx >> sy >> ex >> ey;
//
//        Simple<double> f;
//        Eigen::VectorXd x(2); 
//        x.fill(1);
//
//        cout << "\n[" << x[0] << "," << x[1] << "] to ";
//        BfgsSolver<Simple<double>> solver;
//        solver.minimize(f, x);
//        cout << "[" << x[0] << "," << x[1] << "]\n" << endl;
//
//        cout << (x[0] - sx) / (x[1] - sy) << " =???= " << (x[0] - ex) / (x[1] - ey) << endl;
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
