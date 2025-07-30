#include <bits/stdc++.h>
#include <algorithm>
#include <iomanip>
#include <numeric>

using namespace std;

namespace gauss_elimination {
const long double EPS = 1e-11;
const int INF = 2; // it doesn't actually have to be infinity or a big number

int gauss (vector < vector<long double> > a, vector<long double> & ans) {
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;
    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i)
            if (abs (a[i][col]) > abs (a[sel][col]))
                sel = i;
        if (abs (a[sel][col]) < EPS)
            continue;
        for (int i=col; i<=m; ++i)
            swap (a[sel][i], a[row][i]);
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row) {
                double c = a[i][col] / a[row][col];
                for (int j=col; j<=m; ++j)
                    a[i][j] -= a[row][j] * c;
            }
        ++row;
    }

    ans.assign (m, 0);
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];
    for (int i=0; i<n; ++i) {
        double sum = 0;
        for (int j=0; j<m; ++j)
            sum += ans[j] * a[i][j];
        if (abs (sum - a[i][m]) > EPS)
            return 0;
    }

    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return INF;
    return 1;
}
}

long double solve(int players) {
  if (players == 1) return 0;
  // cerr << "Player: " << players << endl;
  constexpr int dice = 6;
  constexpr int moves [] = {+1, +1, 0, 0, -1, -1};
  int half = players / 2;

  vector<long double> probability(half + 1, 2.00 / players);
  probability[0] /= 2;
  if (!(players & 1)) probability.back() /= 2;

  auto update = [&players](int current_position, int change) {
    current_position += change;
    current_position = (current_position % players + players) % players;
    return current_position;
  };

  auto calculate_min_distance = [&players](int pos_1, int pos_2) {
    if (pos_1 > pos_2) swap(pos_1, pos_2);
    int value = pos_2 - pos_1;
    return min(value, players - value);
  };

  vector<vector<long double>> matrix_0(half, vector<long double>(half, 0.00));
  vector<long double> equal_0(half, 0.00);

  for (int dist = 1; dist <= half; ++ dist) {
    matrix_0[dist - 1][dist - 1] = 1;
    int pos_1 = 0;
    int pos_2 = dist;
    vector<long double> probability(5, 0.0);
    for (int roll = 0; roll < dice; ++ roll) {
      for (int _roll = 0; _roll < dice; ++ _roll) {
        auto new_dist = calculate_min_distance(update(pos_1, moves[roll]), update(pos_2, moves[_roll]));
        int index = new_dist - dist + 2;
        probability[index] += (1 / 36.00);
      }
    }
    for (int offset = 0; offset < 5; ++ offset) {
      int value = offset + dist - 2;
      value = (value % players + players) % players;
      value = min(value, players - value);
      if (!value) equal_0[dist - 1] += probability[offset];
      else matrix_0[dist - 1][value - 1] -= probability[offset];
    }
  }

  auto new_matrix = matrix_0;
  vector<long double> ans(half, 0);
  for (int i = 0; i < half; ++ i) {
    new_matrix[i].push_back(1);
  }
  gauss_elimination::gauss(new_matrix, ans);
  for (int i = 0; i < half; ++ i) {
    new_matrix[i].back() = 2 * ans[i] - 1;
  }
  ans.assign(half, 0);
  gauss_elimination::gauss(new_matrix, ans);
  long double sum = 0;
  for (int i = 0; i < half; ++ i) {
    sum += ans[i] * probability[i + 1];
  }
  return sum + solve(players - 1);
}

//2.38955315e11
int32_t main () {
  cerr << fixed << setprecision(10);
  cerr << solve(500) << endl;
  return 0;
}