#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

#include <idn/common/macro.hpp>
#include <idn/evaluator/ast_node_base.hpp>
#include <idn/evaluator/build_ast.hpp>
#include <idn/evaluator/capi.hpp>
#include <idn/solver/rk4.hpp>
#include <string_view>
#include "csv.hpp"

idn::evaluator::ast::BaseNodePtr GetExpression(std::string_view prompt) {
  std::cout << prompt;
  std::string line;
  std::getline(std::cin, line);
  return idn::evaluator::BuildAstFromString(line);
}

double GetDouble(std::string_view prompt) {
  double var = 0;
  std::cout << prompt;
  std::cin >> var;
  return var;
}

int main(int argc, char** argv) {
  try {
    auto expr = GetExpression("y'(x) = ");
    auto x_0 = GetDouble("x_0 = ");
    auto y_0 = GetDouble("y_0 = ");
    auto x_1 = GetDouble("x_1 = ");
    auto dx = GetDouble("dx = ");

    auto p = idn::solver::rk4::Params()
      .SetX0(x_0)
      .SetY0(y_0)
      .SetX1(x_1)
      .SetDx(dx)
      .SetCtx(&expr);

    auto [xs, ys] = idn::solver::rk4::Solve(idn_parser_function_ctx_call, p);
    idn::cli::GenerateCSVReport(xs, ys);
  } catch (...) {
    throw;
  }

  return EXIT_SUCCESS;
}