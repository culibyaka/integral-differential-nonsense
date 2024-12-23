#pragma once
#include <vector>

namespace idn::solver::rk4 {

using Value = float;
using Array = std::vector<Value>;
using ArrayRef = Array&;
using ArrayCref = const Array&;

struct Params {
  Value x_0;
  Value y_0;
  Value x_1;
  Value dx;
  void* ctx = nullptr;

  Params() = default;

  Params& SetX0(Value x) { x_0 = x; return *this; };
  Params& SetY0(Value y) { y_0 = y; return *this; };
  Params& SetX1(Value x) { x_1 = x; return *this; };
  Params& SetDx(Value d) { dx = d; return *this; };
  template <typename T>
  Params& SetCtx(T* p) { ctx = reinterpret_cast<void*>(p); return *this; };
  Params& SetN(size_t n) { dx = (x_1 - x_0) / (n + 1); return *this; }

  size_t GridSize() const { return (x_1 - x_0) / dx + 1; }
};

// @breif ф-ия вида f(x, y) для решения уравнения вида y' = f(x, y)
using FuncType = float (*)(void*, float, float);

extern "C" float SolveStep(FuncType func, void* ctx, float t, float y, float dt);

[[nodiscard("solution can't be discarded")]]
std::pair<Array, Array> Solve(FuncType func, Params p);

}  // namespace idn::solver::rk4
