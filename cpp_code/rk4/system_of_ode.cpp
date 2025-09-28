#include <iostream>
#include <vector>
#include <array>
#include <cmath>

using namespace std;

using State = array<double, 2>; 

State f(double t, const State& x) {
    double x1 = x[0];
    double x2 = x[1];
    double dx1 = x2;
    double dx2 = 10.0 - 5.0 * x1 - 6.0 * x2;
    return {dx1, dx2};
}

State rk4_step(double t, const State& x, double h) {
    State k1 = f(t, x);

    State xk2 = { x[0] + 0.5 * h * k1[0],
                  x[1] + 0.5 * h * k1[1] };
    State k2 = f(t + 0.5 * h, xk2);

    State xk3 = { x[0] + 0.5 * h * k2[0],
                  x[1] + 0.5 * h * k2[1] };
    State k3 = f(t + 0.5 * h, xk3);

    State xk4 = { x[0] + h * k3[0],
                  x[1] + h * k3[1] };
    State k4 = f(t + h, xk4);

    State xn = {
        x[0] + (h / 6.0) * (k1[0] + 2.0 * k2[0] + 2.0 * k3[0] + k4[0]),
        x[1] + (h / 6.0) * (k1[1] + 2.0 * k2[1] + 2.0 * k3[1] + k4[1])
    };
    return xn;
}

int main() {
    // Parameters
    double t0 = 0.0;
    double t_end = 5.0;
    double h = 1e-4; // step size

    // Time grid
    int N = static_cast<int>((t_end - t0) / h);
    vector<double> t(N + 1);
    for (int i = 0; i <= N; ++i) {
        t[i] = t0 + i * h;
    }

    vector<State> x(N + 1);

    x[0] = {0.0, 5.0};

    for (int n = 0; n < N; ++n) {
        x[n + 1] = rk4_step(t[n], x[n], h);
    }

    cout << "t=" << t.back()
              << "  y=" << x.back()[0]
              << "  y'=" << x.back()[1] << '\n';

    return 0;
}