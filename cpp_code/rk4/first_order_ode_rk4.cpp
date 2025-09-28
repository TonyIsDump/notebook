#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
double f(double x,double y)
{
    return y/(1+sin(x));
}
int main()
{
    double f0,f1,f2,f3;
    double T = 3.0,dt = 0.0001,x = 0.0 ,y = 1.0;
    int N = T/dt;
    for(int i = 0; i < N;i++)
    {
        f0 = f(x,y);
        f1 = f(x + dt/2, y + dt*f0/2);
        f2 = f(x + dt/2, y + dt*f1/2);
        f3 = f(x + dt, y + dt*f2);
        y = y + dt/6*(f0 + 2*f1 + 2*f2 + f3);
        x += dt;
    }
    cout<<y;
    return 0;
}