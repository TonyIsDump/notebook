#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double f(double x,double y){
    return x+y;
}

int main() {
    double T = 1.0;
    double dt = 0.0000001;
    int N = T/dt;
    //vector<double> y = {0,0};
    double y_value = 0;
    double x = 0;
    for (int i = 0; i < N ; i++)
    {
        //y_value = y[1];
        y_value = y_value + dt*f(x,y_value);
       // y.erase(y.begin());
       // y.insert(y.begin() + 1, y_value);
        x +=dt;
    }

    cout<<y_value;
    return 0;
}