#include <gtest/gtest.h>
#include <idn/evaluator/AST.hpp>
#include <memory>

static idn::parser::ast::BaseNodePtr GetX() {
  return std::make_unique<idn::parser::ast::X>();
}

static idn::parser::ast::BaseNodePtr GetY() {
  return std::make_unique<idn::parser::ast::Y>();
}

static idn::parser::ast::BaseNodePtr GetConst(double x) {
  return std::make_unique<idn::parser::ast::Const>(x);
}

// NULLARY

TEST(NullaryOperation, Const) {
  const auto const_ = std::make_unique<idn::parser::ast::Const>(42);
  EXPECT_DOUBLE_EQ(const_->Evaluate(1, 0), 42);
}

// UNARY

TEST(UnaryOperation, X) {
  const auto x = std::make_unique<idn::parser::ast::X>();
  EXPECT_DOUBLE_EQ(x->Evaluate(52, 42), 52);
}

TEST(UnaryOperation, Y) {
  const auto y = std::make_unique<idn::parser::ast::Y>();
  EXPECT_DOUBLE_EQ(y->Evaluate(52, 42), 42);
}

TEST(UnaryOperation, UnaryMinus) {
  const auto uminus = std::make_unique<idn::parser::ast::UnaryMinus>(GetX());
  EXPECT_DOUBLE_EQ(uminus->Evaluate(52, 42), -52);
}

TEST(UnaryOperation, Sin) {
  const auto sin = std::make_unique<idn::parser::ast::Sin>(GetX());
  EXPECT_DOUBLE_EQ(sin->Evaluate(52, 42), std::sin(52));
}

TEST(UnaryOperation, Cos) {
  const auto cos = std::make_unique<idn::parser::ast::Cos>(GetX());
  EXPECT_DOUBLE_EQ(cos->Evaluate(52, 42), std::cos(52));
}

TEST(UnaryOperation, Tan) {
  const auto tan = std::make_unique<idn::parser::ast::Tan>(GetX());
  EXPECT_DOUBLE_EQ(tan->Evaluate(52, 42), std::tan(52));
}

TEST(UnaryOperation, Asin) {
  const auto asin = std::make_unique<idn::parser::ast::Asin>(GetX());
  static constexpr auto alpha = std::numbers::pi / 5;
  EXPECT_DOUBLE_EQ(asin->Evaluate(alpha, 42), std::asin(alpha));
}

TEST(UnaryOperation, Acos) {
  const auto acos = std::make_unique<idn::parser::ast::Acos>(GetX());
  static constexpr auto alpha = std::numbers::pi / 5;

  EXPECT_DOUBLE_EQ(acos->Evaluate(alpha, 42), std::acos(alpha));
}

TEST(UnaryOperation, Atan) {
  const auto atan = std::make_unique<idn::parser::ast::Atan>(GetX());
  EXPECT_DOUBLE_EQ(atan->Evaluate(52, 42), std::atan(52));
}

TEST(UnaryOperation, Log) {
  const auto log = std::make_unique<idn::parser::ast::Log>(GetX());
  EXPECT_DOUBLE_EQ(log->Evaluate(52, 42), std::log(52));
}

// BINARY

TEST(BinaryOperation, Plus) {
  const auto plus = std::make_unique<idn::parser::ast::Plus>(GetX(), GetY());
  EXPECT_DOUBLE_EQ(plus->Evaluate(2, 3), 5);
}

TEST(BinaryOperation, Minus) {
  const auto minus = std::make_unique<idn::parser::ast::Minus>(GetX(), GetY());
  EXPECT_DOUBLE_EQ(minus->Evaluate(2, 3), -1);
}

TEST(BinaryOperation, Multiply) {
  const auto multiply =
      std::make_unique<idn::parser::ast::Multiply>(GetX(), GetY());
  EXPECT_DOUBLE_EQ(multiply->Evaluate(2, 3), 6);
}

TEST(BinaryOperation, Divide) {
  const auto divide =
      std::make_unique<idn::parser::ast::Divide>(GetX(), GetY());
  EXPECT_DOUBLE_EQ(divide->Evaluate(2, 3), 2.0 / 3.0);
  EXPECT_TRUE(std::isinf(divide->Evaluate(2, 0)));
}

TEST(BinaryOperation, Pow) {
  const auto multiply = std::make_unique<idn::parser::ast::Pow>(GetX(), GetY());
  EXPECT_DOUBLE_EQ(multiply->Evaluate(2, 3), 8);
}
