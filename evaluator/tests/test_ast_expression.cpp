#include <gtest/gtest.h>
#include <idn/evaluator/AST.hpp>
#include <memory>

TEST(Expression, Basic) {
  using idn::parser::ast::Const, idn::parser::ast::X, idn::parser::ast::Y,
      idn::parser::ast::Plus, idn::parser::ast::Sin, idn::parser::ast::Pow;

  const auto expr =
      std::make_unique<Pow>(std::make_unique<Sin>(std::make_unique<Plus>(
                                std::make_unique<X>(), std::make_unique<Y>())),
                            std::make_unique<Const>(2));

  static constexpr auto kX = std::numbers::pi;
  static constexpr auto kY = std::numbers::pi / 2;

  EXPECT_DOUBLE_EQ(expr->Evaluate(kX, kY), std::pow(std::sin(kX + kY), 2));
}