#pragma once

namespace idn::solver::rk4 {

// @breif ф-ия вида f(x, y) для решения уравнения вида y' = f(x, y)
using FuncType = float (*)(float, float);

extern "C" float SolveStep(FuncType func, float t, float y, float dt);

}  // namespace idn::solver::rk4
