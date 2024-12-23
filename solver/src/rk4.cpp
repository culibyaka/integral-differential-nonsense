#include <idn/solver/rk4.hpp>

namespace idn::solver::rk4 {

static Array LinearGrid(Params p) {
  Array xs(p.GridSize());
  for (size_t i = 0; i < xs.size(); ++i) {
    xs[i] = p.x_0 + p.dx * i;
  }
  return xs;
}

std::pair<Array, Array> Solve(FuncType func, Params p) {
  Array xs = LinearGrid(p);
  Array ys; ys.reserve(p.GridSize());
  ys.push_back(p.y_0);

  for (size_t i = 1; i < xs.size(); ++i) {
    ys.push_back(SolveStep(func, p.ctx, xs[i-1], ys[i-1], p.dx));
  }

  return {xs, ys};
}

}