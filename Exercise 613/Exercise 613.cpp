#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>

int main() {
    std::cout << std::fixed << std::setprecision(11);
    const double X = 4.0;
    const double Y = 3.0;
    const double PI = 3.14159265358979323846;

    const double A = ::asin(3.0/5.0);
    for (double eps = 1;; eps *= .618) {
        double sum = 0;
        uint64_t iter = 0;
        for (double angle = 0; angle < 2 * PI; ++iter, angle += eps) {
            if (angle < PI/2) {
                sum += 1.0;
            }
            else if (angle < PI - A) {
                double x = -cos(angle);
                double y = sin(angle);
                double x0 = x * (Y/y);
                assert(x0 >= 0 && x0 <= X);
                sum += (X - x0) / X;
            }
            else if (angle < 2*PI - A) {
                // P = 0
            }
            else {
                double x = cos(angle);
                double y = -sin(angle);
                double y0 = y * (X/x);
                assert(y0 >= 0 && y0 <= Y);
                sum += (Y - y0) / Y;
            }
        }
        std::cout << (sum / iter) << ", iter=" << iter << '\n';
    }
}