#include <iostream>
#include <cmath>
#include <chrono>
#include <array>
#define LIM 3'000'000
using ull = unsigned long long;
using map_arr = std::array<int, LIM>;
unsigned int l(int x, int y) {
  int ret = 1;
  unsigned long long cur = y;
  while (cur > 1) {
    cur *= cur;
    cur %= x++;
    ++ret;
  }
  return ret;
}
map_arr nodes, prevnodes;
int main() {
  int longest_from_here = 0;
  auto start = std::chrono::high_resolution_clock::now();
#pragma omp parallel for reduction(max:longest_from_here)
  for (int y = 2; y < LIM; ++y) {
    int ll = l(LIM, y);
    longest_from_here = std::max(longest_from_here, ll);
    nodes[y] = ll;
  }
  auto postp = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> diff1 = postp - start;
  std::cout << "Finished parallel part in " << diff1.count() << " seconds."
            << std::endl;
  int x = LIM - 1;
  int answer = longest_from_here;
  auto previter = std::chrono::high_resolution_clock::now();
  while (x > 2) {
    if (x % (LIM/100) == 0) {
      auto now = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> diff2 = now - previter;
      std::cout << "x = " << x << ", " << std::floor(100 - 100.0 * x / LIM)
                << "% done, took " << diff2.count()
                << " seconds, best so far: " << answer << std::endl;
      previter = now;
    }
    prevnodes.fill(0);
    #pragma omp parallel for reduction(max:longest_from_here)
    for (ull qp = 0; qp <= (x - 1) / 2; ++qp) {
      ull q = (qp * qp) % (x - 1);
      ull y = (q * q) % x;
      int v = nodes[y];
      if (y == 1 || y == 0) {
        if (q < x && q > 0) prevnodes[q] = 1;
      }
      if (q != 0 && q != 1) {
        longest_from_here = std::max(longest_from_here, v + 1);
        prevnodes[q] = v + 1;
      }
    }
    nodes = prevnodes;
    answer = std::max(answer, longest_from_here);
    --x;
  }
  ++answer;
  std::cout << answer << std::endl;
  return 0;
}