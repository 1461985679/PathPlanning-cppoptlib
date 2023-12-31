#include<bits/stdc++.h>
#include <cppoptlib/meta.h>
#include <cppoptlib/solver/lbfgsbsolver.h>
#include <cppoptlib/boundedproblem.h>

// nolintnextline
using namespace cppoptlib;
using namespace std;


double sx, sy,spsi, ex, ey,epsi;
int num;

const double PI = 3.1415926;

struct S_PointXY
{
    double X;
    double Y;
    double Psi;
    void see() {
        cout << "(" << X << "," << Y << "),";
    }
    bool operator == (const S_PointXY& n)const {
        if (X != n.X)return false;
        if (Y != n.Y)return false;
        if (Psi != n.Psi)return false;
        return true;
    }
};

bool EqualPosition(S_PointXY a, S_PointXY b) {
    if (a.X != b.X)return false;
    if (a.Y != b.Y)return false;
    return true;
}

template<typename T>
class GridPathPlanning : public BoundedProblem<T> {
public:
    using Superclass = BoundedProblem<T>;
    using typename Superclass::TVector;
    using TMatrix = typename Superclass::THessian;


    const vector<vector<double> > grid;// 栅格地图

    GridPathPlanning(const vector<vector<double> >& grid_) :grid(grid_),
        Superclass(2) {}


    double SQUARE_SUM(double a, double b) {
        return a * a + b * b;
    }
    double Sign(double a) {
        return a > 0 ? 1 : -1;
    }
    // 角度变换到[-pi，pi]之间
    double ModPI(double theta) {
        theta = fmod(theta, 2 * PI);
        if (theta > PI)
            theta -= 2.0 * PI;
        else if (theta <= -PI)
            theta += 2.0 * PI;
        return theta;
    }
    


    // 欧氏距离
    double EuclideanDistance(S_PointXY pos0, S_PointXY pos1) {
        return EuclideanDistance(pos0.X, pos0.Y, pos1.X, pos1.Y);
    }
    double EuclideanDistance(double x0, double y0, double x1, double y1) {
        return sqrt(pow(x0 - x1, 2) + pow(y0 - y1, 2)) + 1;// 距离至少为1 否则重复点就没权值了
    }

    // 曲线距离
    double fixedCruvatureDistance(const vector<S_PointXY>& pathPoints) {
        double sum = 0;
        for (int i = 0; i < pathPoints.size() - 1; i++) {
            sum += EuclideanDistance(pathPoints[i], pathPoints[i + 1]);
        }
        return sum;
    }


    // 划线法
    // 把两点链接，判断是直线链接还是曲线链接
    // 直线连接用bresenham算法，曲线链接用定曲率行走算法 link point to point
    vector<S_PointXY> linkP2P(S_PointXY p0, S_PointXY p1) {
        return move(linkP2P(p0.X, p0.Y, p0.Psi, p1.X, p1.Y, p1.Psi));
    }
    vector<S_PointXY> linkP2P(double x0,double y0,double psi0,double x1,double y1,double psi1) {
        vector<S_PointXY> track;

        double ePsi1, ePosp0p1;
        double Psip0p1;

        Psip0p1 = atan2(y1 - y0, x1 - x0);
        ePsi1 = ModPI(Psip0p1 - psi0);
        ePosp0p1 = sqrt(SQUARE_SUM(y1 - y0, x1 - x0));

        double Ctr1[2];

        double Disp1C1;

        //直线
        if (fabs(ePsi1) < 2.0 * PI / 32766.0) {
            if (ePosp0p1 > 0.01) {
                psi1 = Psip0p1;
            }
            cerr << "stright 1" << endl;;
            return move(linkP2P_DirectPart(x0, y0, psi0, x1, y1));
        }

        Ctr1[0] = x0 - sin(psi0) * 2 * Sign(ePsi1);
        Ctr1[1] = y0 + cos(psi0) * 2 * Sign(ePsi1);

        Disp1C1 = sqrt(SQUARE_SUM(y1 - Ctr1[1], x1 - Ctr1[0]));
        if (Disp1C1 < 2 || fabs(fabs(ePsi1) - PI) < 0.1) {
            psi1 = Psip0p1;
            cerr << "stright 2" << endl;;
            return move(linkP2P_DirectPart(x0, y0, psi0, x1, y1));
        }


        double Radius = fabs(ePosp0p1 / 2 / sin(ePsi1));
        //返回曲线
        psi1 = ModPI(psi0 + ePsi1 * 2);

        vector<S_PointXY>roverTrack = linkP2P_RoverPart(x0, y0, psi0, x1, y1, psi1);

        // 把弧线映射为整数
    	for(int i=0;i<roverTrack.size();i++){
    		roverTrack[i].X = round(roverTrack[i].X);
    		roverTrack[i].Y = round(roverTrack[i].Y);
    	}
        // 一个迭代器 用来村unique进行队列去重以后的返回值用以删除多余的节点
        vector<S_PointXY>::iterator iter = unique(roverTrack.begin(), roverTrack.end(), EqualPosition);
        roverTrack.erase(iter, roverTrack.end());

        return move(roverTrack);
    }
    // 两点中间经过的直线栅格点 Bresenham算法
    vector<S_PointXY> linkP2P_DirectPart(S_PointXY p0,S_PointXY p1) {
        return move(linkP2P_DirectPart(p0.X, p0.Y,p0.Psi, p1.X, p1.Y));
    }
    
    vector<S_PointXY> linkP2P_DirectPart(double x0, double y0,double psi0 ,double x1, double y1) {
        // 初始化变量
        vector<S_PointXY> directTrack;
        int dx = abs(x1 - x0); // x方向的距离
        int dy = abs(y1 - y0); // y方向的距离
        int stepx = (x0 < x1) ? 1 : -1; // x方向的步长
        int stepy = (y0 < y1) ? 1 : -1; // y方向的步长
        int offset = dx - dy; // 误差
        int xp = x0; // 当前的x坐标
        int yp = y0; // 当前的y坐标

        // 循环直到到达终点
        while (true) {
            // 累加当前栅格的权值
            directTrack.push_back({ double(xp),double(yp),psi0});
            // 如果到达终点，退出循环
            if (xp == x1 && yp == y1) break;
            if (xp < 0 || yp < 0 || xp >= grid.size() || yp >= grid.size()) {
                cout << "(" << x0 << "," << y0 << "),"<<psi0;
                cout << "(" << x1 << "," << y1 << "),";
                cerr << "直线链接法超出边界"<<endl;
                break;
            }
            // 计算下一个栅格的坐标
            int offset_ = 2 * offset;
            if (offset_ > -dy) {
                offset -= dy;
                xp += stepx;
            }
            if (offset_ < dx) {
                offset += dx;
                yp += stepy;
            }
        }
        // 返回权值之和   
        return move(directTrack);
    }

    // 定曲率划线法  这里还需要详细更改
    vector<S_PointXY> linkP2P_RoverPart(S_PointXY p0, S_PointXY p1) {
        // move可以节省内存和时间，直接移动这个points而不是复制里面的每个元素
        return move(linkP2P_RoverPart(p0.X,p0.Y,p0.Psi,p1.X,p1.Y,p1.Psi));
    }
    vector<S_PointXY> linkP2P_RoverPart(double x0, double y0, double psi0, double x1, double y1, double psi1) {


        vector<S_PointXY> roverTrack;// 曲线点集

        double PsiTmp;
        double PosTmp[2];
        S_PointXY tmp;


        double Psip0p1 = atan2(y1 - y0, x1 - x0);
        double ePsi1 = ModPI(Psip0p1 - psi0);
        double ePosp0p1 = sqrt(SQUARE_SUM(y1 - y0, x1 - x0));
        double radius = fabs(ePosp0p1 / 2 / sin(ePsi1));

        PosTmp[0] = x0;
        PosTmp[1] = y0;
        PsiTmp = psi0;

        tmp.X = PosTmp[0];
        tmp.Y = PosTmp[1];
        tmp.Psi = PsiTmp;

        double dis_cur = 1 / radius * Sign(ePsi1);
        double dis_length = fabs(ePsi1) * radius * 2;
        double dis_flag = true;

        unsigned int j, StepNum;
        double PsiNext;

        dis_length = fabs(dis_length);
        // 打点精度 StepNum = 打的点的数量-1  因为起点已经被压入了
        // 这里用直线距离 * 3的数量打点 可以基本保证打到线上所有点
        StepNum = static_cast<unsigned int>(int(EuclideanDistance(x0, y0, x1, y1) * 3));
        if (fabs(dis_cur) < 1e-5) {
            for (size_t k = 0; k < StepNum; ++k) {
                if (dis_flag) {
                    PosTmp[0] += dis_length * cos(PsiTmp) / StepNum;
                    PosTmp[1] += dis_length * sin(PsiTmp) / StepNum;
                }
                else {
                    PosTmp[0] -= dis_length * cos(PsiTmp) / StepNum;
                    PosTmp[1] -= dis_length * sin(PsiTmp) / StepNum;
                }
                roverTrack.push_back({ PosTmp[0],PosTmp[1],PsiTmp });
            }

        }
        else {
            StepNum = max(static_cast<unsigned int>(StepNum), static_cast<unsigned int>(fabs(dis_length * dis_cur) / 2));
            for (j = 0; j < StepNum; ++j) {
                PsiNext = PsiTmp + dis_length * dis_cur / StepNum;
                if (dis_flag) {
                    PosTmp[0] -= (sin(PsiTmp) - sin(PsiNext)) / dis_cur;
                    PosTmp[1] += (cos(PsiTmp) - cos(PsiNext)) / dis_cur;
                }
                else {
                    PosTmp[0] += (sin(PsiTmp) - sin(PsiNext)) / dis_cur;
                    PosTmp[1] -= (cos(PsiTmp) - cos(PsiNext)) / dis_cur;
                }
                PsiTmp = PsiNext;
                roverTrack.push_back({ PosTmp[0],PosTmp[1],PsiTmp });
            }
        }
        roverTrack.push_back({ x1,y1,PsiTmp });
        

        return move(roverTrack);
    }

    // 计算从(x0, y0)到(x1, y1)的路径上的栅格的权值之和
    double LinkGridValue(vector<S_PointXY>& pathPoints) {
        double sum = 0;
        for (int i = 0; i < pathPoints.size(); i++) {
            int x_ = pathPoints[i].X;
            int y_ = pathPoints[i].Y;
            if (x_ >= grid.size() || x_ < 0 || y_ >= grid.size() || y_ < 0) {
                for (int j = 0; j < pathPoints.size(); j++) {
                    pathPoints[j].see();
                    cout << " ";
                }
                cout << endl;
                assert(0);
            }
            sum += grid[x_][y_];
        }
        return sum;
    }

    // this is just the objective (NOT optional)
    T value(const TVector& x) {



        // 把起点和终点加上中间点合起来
        vector<S_PointXY> points = { {sx,sy,spsi}};
        for (int i = 0; i < x.size(); i += 2) {
            points.push_back({ x[i],x[i + 1],0 });
        }
        points.push_back({ ex,ey,epsi});

        // loss = 两两点之间的(定曲率路线长度 * 两点中间经过的曲线的地图权值)之和
        double sumValue = 0;
        for (int i = 0; i < points.size() - 1; i++) {
            vector<S_PointXY> pathPoints = linkP2P(points[i], points[i + 1]);
            sumValue += fixedCruvatureDistance(pathPoints) * LinkGridValue(pathPoints);
        }

        //cout << sumValue << ",,,\n";
        return sumValue;
    }
};
// 定曲率，1中间点，栅格地图
int main(int argc, char const* argv[]) {
    const vector<vector<double> > grid = {
    {0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 0, 0, 1, 1, 1, 1, 0},
    {4, 4, 4, 4, 2, 2, 4, 4, 2, 1},
    {1, 1, 1, 1, 1, 1, 1, 3, 1, 1},
    {0, 0, 0, 0, 0, 1, 0, 0, 1, 3},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 3},
    {2, 2, 2, 2, 2, 2, 2, 2, 1, 3},
    {3, 3, 3, 3, 3, 3, 3, 0, 0, 3},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    GridPathPlanning<double> f(grid);
    int _ = 999;
    while (_--) {
        cout << "g me 2 pos:\n";
        cin >> sx >> sy >>spsi>> ex >> ey >>epsi;

        GridPathPlanning<double> f(grid);
        Eigen::VectorXd x(2); // 修改x的维数 2代表着x0,y0 一个中间点
        x.fill(3);

        // 设置边界约束
        Eigen::VectorXd lb(2);// 下界
        Eigen::VectorXd ub(2);// 上界
        lb << 0, 0;
        ub << grid.size() - 1, grid.size() - 1;
        f.setBoxConstraint(lb, ub);

        cout << "\n[" << x[0] << "," << x[1] << "] to ";
        LbfgsbSolver<GridPathPlanning<double> > solver;
        solver.minimize(f, x); // 只传入x这个参数
        cout << "[" << (int)x[0] << "," << (int)x[1] << "]\n" << endl;


        cout << "f in argmin " << f(x) << endl;
        cout << "Solver status: " << solver.status() << endl;
        cout << "Final criteria values: " << endl << solver.criteria() << endl;


    }
    return 0;
}
