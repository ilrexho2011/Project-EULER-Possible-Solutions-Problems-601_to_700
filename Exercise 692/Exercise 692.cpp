#include <iostream>
#include <vector>

template <typename T> 
bool solve(T& state, int m, int x) 
{
  if (m <= x) 
    return true;

  int n = m - x; 
  for (int i = 1; i <= std::min(n, 2*x); ++i) {
    if (solve(state, n, i))
      return false;
  }  
  return true;
}

int main(void)
{
  std::vector<std::vector<int>> state;
  state.push_back(std::vector<int>{});

  static constexpr int N = 50;
  for (int n = 1; n < N; ++n) {
    state.push_back(std::vector<int>{});
    state[n].push_back(false);
    for (int x = 1; x <= n; ++x)
      state[n].push_back(solve(state, n, x));
  }  

  for (int i = 1; i < N; ++i) {
    int val = i; 
    for (int j = 1; j <= i; ++j) {
      if (state[i][j]) {
        val = j; 
        break;
      }  
    }  
    std::cout << val << " ";
  }  
  std::cout << "\n";
  return 0; 
}