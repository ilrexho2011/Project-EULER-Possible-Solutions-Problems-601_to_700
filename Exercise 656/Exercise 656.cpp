#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class S {
  public:
    S(uint64_t alpha_sqr, uint64_t max_x) {
      this->max_x = max_x;
      double alpha = sqrt(static_cast<double>(alpha_sqr));
      uint64_t max_x_sqr = max_x * max_x;
      uint64_t num_l = floor(alpha);
      uint64_t den_l = 1U;
      uint64_t num_u = num_l + 1U;
      uint64_t den_u = 1U;
      // Note that ((num_u * den_l) - (den_u * num_l)) == 1U.
      while (max_x_sqr > (den_l * den_u)) {
        uint64_t num_m = num_l + num_u;
        uint64_t den_m = den_l + den_u;
        if ((num_m * num_m) > (alpha_sqr * den_m * den_m)) {
          num_u = num_m;
          den_u = den_m;
        } else {
          num_l = num_m;
          den_l = den_m;
        }
      }
      this->num = num_l;
      this->den = den_l;
    }

    uint8_t operator () (uint64_t x) {
      if (x > max_x) {
        std::cerr << "Input out of bounds." << std::endl;
        exit(EXIT_FAILURE);
        return 0U; 
      } else {
        uint64_t t_1 = (num * x) / den;
        uint64_t t_2 = (num * (x - 1U)) / den;
        uint8_t diff = t_1 - t_2;
        return diff;
      }
    }
  private:
    uint64_t max_x;
    uint64_t num;
    uint64_t den;
};

void s_n(uint64_t alpha_sqr, uint64_t n_max, std::vector<uint8_t>& sqnc) {
  S s(alpha_sqr, n_max);
  for (uint64_t i = 1UL; i <= n_max; ++i) {
    sqnc[i] = s(i);
  }
}

bool is_palindrome(std::vector<uint8_t> const& sqnc,
                   size_t start_idx,
                   size_t end_idx) {
  size_t i { start_idx };
  size_t j { end_idx };
  while (i < j) {
    if (sqnc[i] == sqnc[j]) {
      // Do nothing ...
    } else {
      return false;
    }
    i = i + 1;
    j = j - 1;
  }
  return true;
}

void palindrome_indexes(std::vector<uint8_t> const& sqnc,
                        std::vector<size_t>& p_i) {
  p_i.clear();
  for (size_t j = 1; j < sqnc.size(); ++j) {
    if (is_palindrome(sqnc, 1U, j)) {
      p_i.push_back(j);
    }
  }
}

void print_palindrome_indexes(uint64_t alpha_sqr, uint64_t max_idx) {
  std::vector<uint8_t> sqnc(max_idx + 1UL, 0);
  s_n(alpha_sqr, max_idx, sqnc);
  for (uint64_t i = 1; i <= max_idx; ++i) {
    if (is_palindrome(sqnc, 1UL, i)) {
      std::cout << i << std::endl;
    }
  }
}

void squares(std::vector<bool>& sqrs) {
  uint64_t i = 0U;
  uint64_t i_sqr = i * i;
  while (i_sqr < sqrs.size()) {
    sqrs[i_sqr] = true;
    i = i + 1U;
    i_sqr = i * i;
  }
}

// Conjecture 1. The sequence has only two distinct elements a, b.
//               a < b.
//               (a + 1) = b.
//               (a * a) < alpha_sqr < (b * b).
bool verify_alphabet(uint64_t alpha_sqr,
                     std::vector<uint8_t> const& sqnc,
                     uint8_t& a,
                     uint8_t& b) {
  std::unordered_set<uint64_t> distinct_elems;
  for (uint64_t i = 1U; i < sqnc.size(); ++i) {
    distinct_elems.insert(sqnc[i]);
  }
  if (distinct_elems.size() == 2U) {
    auto iter = distinct_elems.begin();
    uint64_t t_1 = *iter;
    ++iter;
    uint64_t t_2 = *iter;
    uint64_t mn = std::min(t_1, t_2);
    uint64_t mx = std::max(t_1, t_2);
    if ((mx - mn) == 1U) {
      uint64_t mn_sqr = mn * mn;
      uint64_t mx_sqr = mx * mx;
      if ((mn_sqr < alpha_sqr) && (alpha_sqr < mx_sqr)) {
        a = mn;
        b = mx;
        return true;
      }
    }
  }
  return false;
}

// Conjecture 2. Of the two distinct elements a, b in the sequence, one of
//               them has a maximum run-length of 1.
bool verify_repeat(std::vector<uint8_t> const& sqnc,
                   uint8_t& r,
                   size_t& f) {
  std::unordered_map<uint64_t, uint64_t> element_run; 
  uint64_t current_run = 1U;
  bool is_first = true;
  for (uint64_t i = 1U; i < sqnc.size(); ++i) {
    if (sqnc[i] == sqnc[i - 1U]) {
      current_run = current_run + 1U;
      if (is_first) {
        is_first = false;
        f = i - 1U;
      }
    } else {
      element_run[sqnc[i]] = std::max(current_run, element_run[sqnc[i]]);
      current_run = 1U;
    }
  }
  assert(element_run.size() == 2U);
  auto iter = element_run.begin();
  uint64_t k_1 = iter->first;
  uint64_t v_1 = iter->second;
  ++iter;
  uint64_t k_2 = iter->first;
  uint64_t v_2 = iter->second;
  if (v_1 == 1U) {
    r = k_2;
  } else if (v_2 == 1U) {
    r = k_1;
  } else {
    return false;
  }
  return (v_1 > 0U) && (v_2 > 0U) && (v_1 != v_2);
}

// Conjecture 3. If i, j, k are three successive palindrome indexes, then
//               (i + k) == 0 (mod j).
bool verify_3_term_mod(std::vector<size_t> const& p_i) {
  for (uint64_t i = 2U; i < p_i.size(); ++i) {
    size_t x = p_i[i - 2U];
    size_t y = p_i[i - 1U];
    size_t z = p_i[i];
    if (((x + z) % y) == 0U) {
      // Fits pattern ...
    } else {
      return false;
    }
  }
  return true;
}

// Conjecture 4. If i, j, k are three successive palindrome indexes, then
//               i = (m * j) - k, for some m >= 2.
//               For 2 <= x < m, sqnc[1] != sqnc[(x * j) - k], 
//                               sqnc[1] == sqnc[i].
bool verify_palindrome_marker(std::vector<uint8_t> const& sqnc,
                              std::vector<size_t> const& p_i,
                              uint8_t r,
                              size_t f) {
  for (size_t i = 2U; i < p_i.size(); ++i) {
    size_t x = p_i[i - 2U];
    size_t y = p_i[i - 1U];
    size_t z = p_i[i];
    size_t cur_idx = (y + y) - x;
    while (cur_idx < z) {
      if (sqnc[cur_idx] == sqnc[1U]) {
        std::cerr << "Failed @0." << std::endl;
        return false;
      }
      cur_idx = cur_idx + y;
    }
    assert(cur_idx == z);
    assert(sqnc[cur_idx] == sqnc[1U]);
  }
  return true;
}

void verify_conjectures(uint64_t t_max, uint64_t n_max) {
  std::vector<bool> sqrs(t_max + 1U, false);
  squares(sqrs);
  for (uint64_t i = 0U; i < sqrs.size(); ++i) {
    if (sqrs[i]) {
      // Ignore squares ...
    } else {
      std::cout << "verifying conjectures for " << i << "." << std::endl;
      std::vector<uint8_t> sqnc(n_max + 1U, 0U);
      s_n(i, n_max, sqnc);
      std::vector<size_t> p_i;
      palindrome_indexes(sqnc, p_i);
      uint8_t a = 0U;
      uint8_t b = 0U;
      uint8_t r = 0U;
      size_t f = 0U;
      assert(verify_alphabet(i, sqnc, a, b));
      assert(verify_repeat(sqnc, r, f));
      assert(verify_3_term_mod(p_i));
      assert(verify_palindrome_marker(sqnc, p_i, r, f));
    }
  }
}

int main(int argc, char** argv) {
  const int DECIMAL_BASE { 10 };
  uint64_t t_max { strtoull(argv[1], nullptr, DECIMAL_BASE) };
  uint64_t n_max { strtoull(argv[2], nullptr, DECIMAL_BASE) };
  std::cout << "t_max = " << t_max << std::endl;
  std::cout << "n_max = " << n_max << std::endl;
  verify_conjectures(t_max, n_max);
  return 0;
}