#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<double> f(double t , vector<double> x) {
    vector<double> vec = {0,0};
    double x1 = x[0];
    double x2 = x[1];
    vec[0] = x2;
    vec[1] = -9.81*x1;
    return vec;
}

vector<double> rk4(vector<double> x , double t, double h)
{
    vector<double> k1 = f(t,x);
    vector<double> xk2 = { x[0] + 0.5 * h * k1[0],
                  x[1] + 0.5 * h * k1[1] };
    vector<double> k2 = f(t + 0.5 * h, xk2);

    vector<double> xk3 = { x[0] + 0.5 * h * k2[0],
                  x[1] + 0.5 * h * k2[1] };
    vector<double> k3 = f(t + 0.5 * h, xk3);

    vector<double> xk4 = { x[0] + h * k3[0],
                  x[1] + h * k3[1] };
    vector<double> k4 = f(t + h, xk4);

    vector<double> xn = {
        x[0] + (h / 6.0) * (k1[0] + 2.0 * k2[0] + 2.0 * k3[0] + k4[0]),
        x[1] + (h / 6.0) * (k1[1] + 2.0 * k2[1] + 2.0 * k3[1] + k4[1])
    };
    return xn;

}
int main()
{
    double t0 = 0.0;
    double t1 = 5.0;
    double h = 1e-4; // step size
    double t;
    int N = (t1-t0)/h;
    vector<double> x = {0.0,5.0};

    for(int i = 0; i < N; i++)
    {
        t = t0 +i*h;
        x = rk4(x,t,h);
    }
    cout <<x[0] << " " <<x[1];

    return 0;
}