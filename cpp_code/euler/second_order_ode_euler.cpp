#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double f(double t,double x,double u){
    return x+2*u;
}

int main() {
    double T = 2.0;
    double dt = 0.0000001;
    int N = T/dt;
    //vector<double> y = {0,0};
    double x = 1 , t = 0 , u = 0;
    double dx, du;
    for (int i = 0; i < N ; i++)
    {
        dx = dt*u;
        du = dt*f(t,x,u);
        x += dx;
        u += du;
        t += dt;
    }

    cout<<x;
    return 0;
}