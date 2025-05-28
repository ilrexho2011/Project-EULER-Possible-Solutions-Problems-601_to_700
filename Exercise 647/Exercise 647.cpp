#include <cstdint>
#include <iostream>

#include "math_utils.h"

uint64_t f_3(uint64_t n) {
  auto result { 0ULL };
  auto i { 1ULL };
  auto done { false };
  do {
    auto b { pe::triangular(i) }; 
    auto two_i_plus_1 { (2ULL * i) + 1ULL };
    auto a { two_i_plus_1 * two_i_plus_1 };
    if ((a > n) || (b > n)) {
      done = true;
    } else {
      result = result + a + b;
    }
    i = i + 1ULL;
  } while (done == false);
  return result;
}

uint64_t f_two_p_plus_1(uint64_t n, uint64_t p) {
  auto result { 0ULL };
  auto two_p_minus_1 { (2ULL * p) - 1ULL };
  auto two_p_minus_3 { (2ULL * p) - 3ULL };
  auto done = false;
  auto lttl_b { two_p_minus_3 };
  auto x = 1ULL;
  do {
    auto b { ((lttl_b * lttl_b * two_p_minus_1) + (lttl_b * two_p_minus_3)) / 2ULL };
    auto lttl_a { (2ULL * x * two_p_minus_1) + 1ULL };
    auto a { lttl_a * lttl_a };
    if ((a > n) || (b > n)) {
      done = true;
    } else {
      result = result + a + b;
    }
    lttl_b = lttl_b + two_p_minus_3;
    x = x + 1ULL;
  } while (done == false);
  return result;
}

uint64_t solve(uint64_t n) {
  auto result { f_3(n) };
  auto p { 2ULL };
  auto done { false };
  do {
    auto contrib { f_two_p_plus_1(n, p) };
    if (contrib == 0ULL) {
      done = true;
    } else {
      result = result + contrib;
    }
    p = p + 1ULL;
  } while (done == false);
  return result;
}


int main(int argc, char** argv) {
  auto n { 1000000000000ULL };
  auto result { solve(n) };
  std::cout << result << std::endl;
  return 0;
}