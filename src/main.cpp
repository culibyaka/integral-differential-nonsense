#include <cassert>
#include <format>
#include <iostream>
#include <vector>
#include "solver/rk4.hpp"

#define UNUSED(x) (void)(x)

extern "C" float f(float);  // NOLINT

static constexpr float kStart = -1.0f;
static constexpr float kEnd = 1.0f;

using Array = std::vector<float>;
using ArrayRef = Array&;
using ArrayCref = const Array&;

void GenerateCSVReport(ArrayCref xs, ArrayCref ys) {
  assert(xs.size() == ys.size());

  std::cout << "x,f\n";
  for (auto i = 0; i < xs.size(); ++i) {
    std::cout << std::format("{},{}\n", xs[i], ys[i]);
  }
}

float Func(float x, float y) {
  UNUSED(y);
  return x;
}

float Last(ArrayCref v) { return v[v.size() - 1]; }

std::pair<Array, Array> Solve(float dx) {
  using idn::solver::rk4::SolveStep;

  const float start = -1, end = 1;
  const auto n = static_cast<std::size_t>((end - start) / dx) + 1;

  Array xs, ys;
  xs.reserve(n), ys.reserve(n);
  xs.push_back(start), ys.push_back(0.5);
  float x = start;

  for (auto i = 0; i < n; ++i) {
    xs.emplace_back(x);
    ys.emplace_back(SolveStep(Func, Last(xs), Last(ys), dx));
    x += dx;
  }

  return {xs, ys};
}

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cout << std::format("usage: {} <step>\n", argv[0]);
    return -1;
  }

  const auto dx = std::atof(argv[1]);
  const auto [xs, ys] = Solve(dx);
  GenerateCSVReport(xs, ys);

  return 0;
}
