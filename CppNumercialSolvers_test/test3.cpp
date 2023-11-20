//#include<bits/stdc++.h>
//#include<cppoptlib/meta.h>
//#include<cppoptlib/problem.h>
//#include<cppoptlib/solver/bfgssolver.h>
//#include<cppoptlib/boundedproblem.h>
//
//// nolintnextline
//using namespace cppoptlib;
//using namespace std;
//
//
//
//double sx, sy, ex, ey;
//int num;//num<100
//int gridSize = 100;
//int grid[100][100];
//
//// we define a new problem for optimizing the Simple function
//// we use a templated-class rather than "auto"-lambda function for a clean architecture
//template<typename T>
//class Simple : public Problem<T> {
//public:
//    using typename Problem<T>::TVector;
//
//    
//    double EuclideanDistance(double x1, double y1, double x2, double y2) {
//        return pow(x1 - x2, 2) + pow(y1 - y2, 2) + 1;//��������Ϊ1 �����ظ����ûȨֵ��
//    }
//    // this is just the objective (NOT optional)
//    T value(const TVector& p) {
//        
//        //ȨֵΪŷ�Ͼ���*����Ȩֵ��������ʹ�ó���׷��ÿ���㶼�͵�Ȩ����������Ȩ������ͣ���������������ÿ���㶼�����ܱ��ϣ�
//        double sumDis = 0;
//        //��㵽��һ���м��
//        sumDis += EuclideanDistance(sx, sy, p[0], p[1]);
//        //�����м�㵽�յ�
//        sumDis += EuclideanDistance(p[p.size() - 2], p[p.size() - 1], ex, ey);
//        //�м��֮��
//
//        //ȥ��
//        map<int,map<int,int> > vis;
//        vis.clear();
//        vis[sx][sy] = 1;
//        vis[ex][ey] = 1;
//        for (int i = 0; i < p.size(); i += 2) vis[p[i]][p[i + 1]] += 1;
//
//
//        for (int i = 2; i < p.size(); i += 2) {
//            double vertexValue = 1;//����ĵ�ͼȨֵ
//            //�жϵ�ͼ�߽�
//            for (int j = i - 2; j <= i + 1; j++) {
//                if (p[j] < 0 || p[j] >= gridSize) vertexValue = 999;
//            }
//            //�ж��Ƿ����ظ��ĵ�
//            if (vis[p[i - 2]][p[i - 1]])vertexValue *= vis[p[i - 2]][p[i - 1]];
//                if (vis[p[i]][p[i + 1]]) vertexValue *= vis[p[i]][p[i + 1]];
//
//            vertexValue *= grid[int(p[i - 2])][int(p[i - 1])] + grid[int(p[i])][int(p[i + 1])];
//            sumDis += (EuclideanDistance(p[i - 2], p[i - 1], p[i], p[i + 1])) * vertexValue;
//        }
//        return sumDis;
//    }
//};
////�ٸ���һЩ�ģ���դ���ͼ������
//int main(int argc, char const* argv[]) {
//
//    int  _(999);
//    while (_--) {
//        cout << "g me 2 pos < 100:" << endl;
//        cin >> sx >> sy >> ex >> ey;
//        cout << "g me 1 num < 10:" << endl;
//        cin >> num;
//        cout << "g me 1 gridSize < 100:" << endl;
//        cin >> gridSize;
//        cout << "g me "<<gridSize<<" gridSize < 100:" << endl;
//        for (int i = 0; i < gridSize; i++) {
//            for (int j = 0; j < gridSize; j++) {
//                cin >> grid[i][j];
//            }
//        }
//        Simple<double> f;
//        //f.setLowerBound(Vector<double>::Zero(DIM));
//        //f.setUpperBound(Vector<double>::Ones(DIM) * 5);
//        Eigen::VectorXd path((num - 2) * 2);
//        path.fill(5);
//        cout << "1" << endl;
//        BfgsSolver<Simple<double>> solver;
//        solver.minimize(f, path);
//        for (int i = 0; i < path.size(); i += 2) {
//            cout << "[" << int(path[i]) << "," << int(path[i + 1]) << "]\n";
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
//
//
//
//
//
//
//
//
////1 1 1 1 1 1 1 1 1 1
////1 1 0 0 0 0 0 0 0 0 
////1 1 1 1 1 1 1 1 1 0 
////4 4 4 4 4 4 4 4 2 1 
////1 1 1 1 1 1 2 3 1 1 
////0 0 0 0 0 1 2 3 1 1 
////1 1 1 1 1 1 2 3 1 1 
////2 2 2 2 2 2 2 3 1 1 
////3 3 3 3 3 3 3 3 1 1 
////1 1 1 1 1 1 1 1 1 1
