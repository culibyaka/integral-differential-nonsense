#include "rk4.hpp"

namespace idn::solver::rk4 {

extern "C" float SolveStep(FuncType func, float t, float y, float dt) {
  const auto k1 = func(t, y);
  const auto k2 = func(t + dt / 2, y + k1 / 2 * dt);
  const auto k3 = func(t + dt / 2, y + k2 / 2 * dt);
  const auto k4 = func(t + dt, y + k3 * dt);
  return y + (k1 + 2 * k2 + 2 * k3 + k4) * dt / 6;
}

}  // namespace idn::solver::rk4