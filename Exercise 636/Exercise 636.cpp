#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <chrono>
#include <map>

const std::vector<int> problem_coefficients = {1,2,2,3,3,3,4,4,4,4};
const int64_t N = 1000000;

const int64_t MOD = 1000000007;
bool composite[N + 1];
std::vector<int64_t> primes;
std::vector<std::vector<int>> partitions_memo[11];
std::map<std::vector<int>, int64_t> F_dp;
int64_t leg[N + 1];
int64_t dp[N + 1];
int64_t fac[20];
int64_t ifac[20];

int64_t legendre(int64_t n, int64_t p) {
  int64_t ans = 0;
  int64_t q = p;
  while (n/q) { ans += n/q; q *= p; }
  return ans;
}

int64_t mod_pow(int64_t a, int64_t b) {
  if (b == 0) return 1;
  if (b & 1) return a * mod_pow(a, b - 1) % MOD;
  return mod_pow(a*a % MOD, b >> 1);
}

int64_t mod_inv(int64_t a) {
  return mod_pow(a, MOD - 2);
}

void partitions_helper(std::vector<std::vector<int>>& results,
  std::vector<int>& pr, int remaining, int cs)
{
  if (remaining == 0) {
    results.push_back(pr);
  } else {
    for (int c = 0; c <= cs; ++c) {
      pr.push_back(c);
      partitions_helper(results, pr, remaining - 1, std::max(cs, c + 1));
      pr.pop_back();
    }
  }
}

std::vector<std::vector<int>> partitions(int n) {
  std::vector<std::vector<int>> result;
  std::vector<int> pr;
  partitions_helper(result, pr, n, 0);
  return result;
}

void generate_dp(std::vector<int> coeff) {
  std::memset(dp, -1, sizeof(dp));
  const int vars = coeff.size();
  dp[0] = 1;
  for (int r = 1; r <= N; ++r) dp[r] = 0;
  for (int i = vars-1; i >= 0; --i) {
    for (int r = 0; r <= N; ++r) {
      dp[r] = dp[r] + (r >= coeff[i]? dp[r - coeff[i]] : 0);
      if (dp[r] >= MOD) dp[r] -= MOD;
    }
  }
}

int64_t F(std::vector<int> coeffs) {
  auto it = F_dp.find(coeffs);
  if (it != F_dp.end()) return it->second;

  generate_dp(coeffs);
  int64_t total = 1;
  for (int p : primes) {
    total = (total * dp[leg[p]]) % MOD;
  }

  for (auto partition : partitions_memo[coeffs.size()]) {
    int components = 0;
    for (int i = 0; i < partition.size(); ++i) {
      components = std::max(components, partition[i] + 1);
    }
    if (components == coeffs.size()) continue;
    std::vector<int> new_coeffs(components, 0);
    for (int i = 0; i < partition.size(); ++i) {
      new_coeffs[partition[i]] += coeffs[i];
    }
    std::sort(new_coeffs.begin(), new_coeffs.end());
    total = (total - F(new_coeffs) + MOD) % MOD;
  }
  return F_dp[coeffs] = total;
}

int main() {
  auto t0 = std::chrono::high_resolution_clock::now();

  fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
  for (int n = 2; n < 20; ++n) {
    fac[n] = n * fac[n-1] % MOD;
    ifac[n] = mod_inv(fac[n]);
  }
  composite[0] = composite[1] = true;
  for (int i = 2; i <= N; ++i) {
    if (!composite[i]) {
      primes.push_back(i);
      leg[i] = legendre(N, i);
      for (int j = i + i; j <= N; j += i) {
        composite[j] = true;
      }
    }
  }
  for (int n = 1; n <= problem_coefficients.size(); ++n) {
    partitions_memo[n] = partitions(n);
  }

  auto answer = F(problem_coefficients);

  std::map<int, int> freq;
  for (int c : problem_coefficients) freq[c]++;
  for (auto pr : freq) {
    answer = answer * ifac[pr.second] % MOD;
  }
  std::cout << answer << '\n';

  auto t1 = std::chrono::high_resolution_clock::now();
  std::cout << "Finished in "
    << std::chrono::duration_cast<std::chrono::seconds>(t1 - t0).count()
    << " seconds.\n";
}