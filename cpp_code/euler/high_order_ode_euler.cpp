#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double f(double t,double x,double u,double v){
    return t*t-x/(1+exp(-t))-sin(t)*sqrt(1+v*v)*u;
}

int main() {
    double T = 4.0;
    double dt = 0.0000001;
    int N = T/dt;
    //vector<double> y = {0,0};
    double x = 1 , t = 0 , u = 2 , v = 3;
    double dx, du,dv;
    for (int i = 0; i < N ; i++)
    {
        dx = dt*u;
        du = dt*v;
        dv = dt*f(t,x,u,v);
        x += dx;
        u += du;
        v += dv;
        t += dt;
    }

    cout<<x;
    return 0;
}