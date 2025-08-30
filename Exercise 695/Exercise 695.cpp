#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <omp.h>
#include <cassert>
#include <iomanip>

std::vector<std::default_random_engine> res;

long double area(long double px, long double py, long double qx, long double qy) {
  return std::abs((px - qx) * (py - qy));
}
long double f(long double p1x, long double p1y, long double p2x,
              long double p2y, long double p3x, long double p3y) {
  long double a = area(p1x, p1y, p2x, p2y);
  long double b = area(p2x, p2y, p3x, p3y);
  long double c = area(p1x, p1y, p3x, p3y);
  return a + b + c - std::min(a, std::min(b, c)) - std::max(a, std::max(b, c));
}
double estimate(unsigned long long samples, int omp_idx) {
  std::uniform_real_distribution<long double> d(0.0, 1.0);
  auto& gen = res[omp_idx];
  auto rand = [&d, &gen]{ return d(gen); };
  long double sum = 0;
  for (int i = 0; i < samples; ++i) {
    long double px1 = rand();
    long double py1 = rand();
    long double px2 = rand();
    long double py2 = rand();
    long double px3 = rand();
    long double py3 = rand();
    sum += f(px1, py1, px2, py2, px3, py3);
  }
  return sum;
}

void initialize_random_state(int num_threads) {
  res.resize(num_threads);
  std::random_device rd;
  std::vector<int> initial_seeds(num_threads);
  std::iota(initial_seeds.begin(), initial_seeds.end(), 0);
  std::seed_seq seq(initial_seeds.begin(), initial_seeds.end());
  std::vector<unsigned int> seeds(num_threads);
  seq.generate(seeds.begin(), seeds.end());
  for (int i = 0; i < num_threads; ++i) {
    res[i].seed(seeds[i]);
  }
}
int main() {
  initialize_random_state(omp_get_max_threads());
  unsigned long long samples = 1e7;
  unsigned long long chunks = 10;
  assert(samples % chunks == 0);
  unsigned long long chunk_size = samples / chunks;
  long double sum = 0;
  std::vector<long double> results(chunks);
  int n = 0;
  unsigned long long totsamples = 0;
  while (true) {
#pragma omp parallel for
    for (int i = 0; i < chunks; ++i) {
      results[i] = estimate(chunk_size, omp_get_thread_num());
    }
    long double ssum = std::accumulate(results.begin(), results.end(), 0.0);
    totsamples += samples;
    sum += ssum;
    long double savg = sum / totsamples;
    long double ssde = 0;
    for (auto x : results) ssde += std::pow(x - savg, 2.0);
    ssde /= totsamples - 1;
    std::cout << "After " << n << " trials, mean is " << std::setprecision(10) << savg << ", variance is " << ssde << std::endl;
    ++n;
    if (ssde < 1e-10) break;
  }
  std::cout << "Total sum: " << std::setprecision(10) << sum << std::endl;
  std::cout << sum/static_cast<long double>(samples) << std::endl;
}