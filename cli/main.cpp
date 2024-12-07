#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>

#include <idn/common/macro.hpp>
#include <idn/evaluator/ast_node_base.hpp>
#include <idn/evaluator/build_ast.hpp>
#include <idn/solver/rk4.hpp>
#include "csv.hpp"

idn::evaluator::ast::BaseNodePtr GetExpression() {
  std::cout << "> ";
  std::string line;
  std::getline(std::cin, line);
  return idn::evaluator::BuildAstFromString(line);
}

double GetVar(std::string_view name) {
  double var = 0;
  std::cout << name << "> ";
  std::cin >> var;
  return var;
}

int main(int argc, char** argv) {
  const auto expr = GetExpression();
  const auto x = GetVar("x");
  const auto y = GetVar("y");

  std::cout << std::endl << expr->Evaluate(x, y) << std::endl;

  return EXIT_SUCCESS;
}