#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

double P(int k, int m) {
    // Step 1: Generate rseq
    std::vector<int> rseq(k * m + m);
    int rlast = 0;
    for (int i = 0; i < rseq.size(); i++) {
        rlast = (i ? (rlast * rlast) % 10007 : 306);
        rseq[i] = rlast;
    }

    // Step 2: Initialize qprob as a 2D vector [k][5] with zeros
    std::vector<std::vector<int>> qprob(k, std::vector<int>(5, 0));
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < m; j++) {
            qprob[i][rseq[i * m + j] % 5]++;
        }
    }

    // Step 3: Initialize dyingProb
    std::vector<double> dyingProb(k, 0.0);
    for (int i = 0; i < k; i++) {
        dyingProb[i] = static_cast<double>(qprob[i][0]) / m;
    }

    // Step 4: Define cycle function
    auto cycle = [&]() {
        std::vector<double> nextDyingProb(k, 0.0);
        for (int i = 0; i < k; i++) {
            nextDyingProb[i] = 
                (static_cast<double>(qprob[i][0]) / m)
                + (static_cast<double>(qprob[i][1]) / m) * (dyingProb[i] * dyingProb[i])
                + (static_cast<double>(qprob[i][2]) / m) * dyingProb[(2 * i) % k]
                + (static_cast<double>(qprob[i][3]) / m) * pow(dyingProb[(i * i + 1) % k], 3)
                + (static_cast<double>(qprob[i][4]) / m) * (dyingProb[i] * dyingProb[(i + 1) % k]);
        }
        dyingProb = nextDyingProb;
    };

    // Step 5: Iterate until convergence
    double ret = dyingProb[0];
    double dif = 1.0;
    while (dif > 1e-10) {
        cycle();
        dif = std::abs(dyingProb[0] - ret);
        ret = dyingProb[0];
        std::cout << std::fixed << std::setprecision(12) << ret << std::endl;
    }

    std::cout << "P(" << k << "," << m << ")=" << std::fixed << std::setprecision(12) << ret << std::endl;
    return ret;
}

// Example usage
int main() {
    P(10, 20);  // replace with desired values of k and m
    return 0;
}
