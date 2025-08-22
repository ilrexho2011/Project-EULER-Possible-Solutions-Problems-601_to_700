#include <iostream>
#include <cinttypes>
#include <vector>
#include <numeric>
#include <iomanip>

using namespace std;

#include <boost/math/distributions/normal.hpp>

double epsilon = 1e-7;
double epsilon2 = 1e-24;

double solve(double a, int64_t till) {
    double answer(0.5);
    vector<pair<double, double>> vals{make_pair(0.0, 0.5)};
    double remaining((M_PI * M_PI) / 6 - 1);
#if 0
    double prev_answer = 0;
#endif
    for (int64_t i = 2; i <= till; ++i) {
        double component = ((double)1.0) / ((double)i) / i;
        vector<pair<double, double>> new_vals;
        for (auto v: vals) {
            if (v.first + remaining < a) {
                continue;
            }

            if (v.first + component > a) {
                answer += v.second / 2.0;
                new_vals.push_back(make_pair(v.first, v.second / 2.0));
            } else {
                new_vals.push_back(make_pair(v.first, v.second / 2.0));
                new_vals.push_back(make_pair(v.first + component, v.second / 2.0));
            }
        }
        remaining -= component;

        sort(new_vals.begin(), new_vals.end(), greater<pair<double, double>>());
        vals.clear();
        for (auto v: new_vals) {
            if (v.second < epsilon2) {
                continue;
            }
            if (vals.empty() || (vals.back().first - v.first) > epsilon) {
                vals.push_back(v);
            } else {
                vals.back().first = vals.back().first * vals.back().second + v.first * v.second;
                vals.back().second += v.second;
                vals.back().first /= vals.back().second;
            }
        }

        if (vals.empty()) {
            break;
        }
#if 0
        if (answer - prev_answer > 1e-8) {
            cout << i << ": " << answer << ", " << answer - prev_answer << " (" << vals.size() << ")" << endl;
            prev_answer = answer;
        }
#endif
    }

    // Approximate by normal distribution.
    boost::math::normal_distribution<double> nd(remaining / 2.0, remaining / boost::math::constants::pi<double>() / 2);
    if (!vals.empty()) {
        for (auto v: vals) {
            answer += v.second * (1.0 - boost::math::cdf(nd, a - v.first));
        }
    }

    return answer;
}

int main() {
    cout << setprecision(15);

    //double answer = solve(0.5, 10000000);
    double answer = solve(0.5, 3000);
    cout << setprecision(8);
    cout << answer << endl;
}