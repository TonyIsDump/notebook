#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

double f(double x) {
    return exp(-x * x);
}

int main() {
    int N = 10000000;
    double a = -10000.0;
    double b = 10000.0;
    //vector<double> X(N);
    double h = (b - a) / N;
    //for (int i = 0; i < N; ++i) {
        //X[i] = a + static_cast<double>(i) * h;  // Cast i to double to prevent overflow
    //}
    double sum_int = 0.0;
    for (int i = 0; i < N-1; i++) {
        sum_int += h*(f(a + h*i)+f(a + h*(1+i))+f(a + h*(2+i))) /3;
    }
    cout << sum_int << endl;
    return 0;
}