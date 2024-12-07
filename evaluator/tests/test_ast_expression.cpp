#include <gtest/gtest.h>
#include <memory>
#include "AST.hpp"

TEST(Expression, Basic) {
  using idn::evaluator::ast::Const, idn::evaluator::ast::X, idn::evaluator::ast::Y,
      idn::evaluator::ast::Plus, idn::evaluator::ast::Sin, idn::evaluator::ast::Pow;

  const auto expr =
      std::make_unique<Pow>(std::make_unique<Sin>(std::make_unique<Plus>(
                                std::make_unique<X>(), std::make_unique<Y>())),
                            std::make_unique<Const>(2));

  static constexpr auto kX = std::numbers::pi;
  static constexpr auto kY = std::numbers::pi / 2;

  EXPECT_DOUBLE_EQ(expr->Evaluate(kX, kY), std::pow(std::sin(kX + kY), 2));
}