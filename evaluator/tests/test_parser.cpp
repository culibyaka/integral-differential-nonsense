#include <gtest/gtest.h>
#include <idn/evaluator/build_ast.hpp>

TEST(Parser, Basic) {
  const auto expr = idn::evaluator::BuildAstFromString(" (1 + x)");
  ASSERT_DOUBLE_EQ(expr->Evaluate(0, 1), 1);
}
