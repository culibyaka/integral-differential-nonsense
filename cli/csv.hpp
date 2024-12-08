#pragma once
#include <idn/solver/rk4.hpp>

namespace idn::cli {

void GenerateCSVReport(solver::rk4::ArrayCref xs, solver::rk4::ArrayCref ys);

}  // namespace idn::cli