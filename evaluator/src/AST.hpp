#pragma once
#include <cmath>
#include <idn/common/assert.hpp>
#include <idn/common/macro.hpp>
#include <idn/evaluator/ast_node_base.hpp>

namespace idn::parser::ast {

// SPECIAL

class X final : public BaseNode {
 public:
  double Evaluate(double x, double y) override {
    UNUSED(y);
    return x;
  }
};

class Y final : public BaseNode {
 public:
  double Evaluate(double x, double y) override {
    UNUSED(x);
    return y;
  }
};

class Const : public BaseNode {
 public:
  explicit Const(double value) : value_(value) {}

  double Evaluate(double x, double y) override {
    UNUSED(x);
    UNUSED(y);
    return value_;
  }

 private:
  const double value_;
};

BaseNodePtr GetX();
BaseNodePtr GetY();

// BINARY

class Plus : public BaseNode {
 public:
  Plus(BaseNodePtr left, BaseNodePtr right)
      : left_(std::move(left)), right_(std::move(right)) {}

  double Evaluate(double x, double y) override {
    return left_->Evaluate(x, y) + right_->Evaluate(x, y);
  }

 private:
  BaseNodePtr left_, right_;
};

class Minus : public BaseNode {
 public:
  Minus(BaseNodePtr left, BaseNodePtr right)
      : left_(std::move(left)), right_(std::move(right)) {}

  double Evaluate(double x, double y) override {
    return left_->Evaluate(x, y) - right_->Evaluate(x, y);
  }

 private:
  BaseNodePtr left_, right_;
};

class Multiply : public BaseNode {
 public:
  Multiply(BaseNodePtr left, BaseNodePtr right)
      : left_(std::move(left)), right_(std::move(right)) {}

  double Evaluate(double x, double y) override {
    return left_->Evaluate(x, y) * right_->Evaluate(x, y);
  }

 private:
  BaseNodePtr left_, right_;
};

class Divide : public BaseNode {
 public:
  Divide(BaseNodePtr left, BaseNodePtr right)
      : left_(std::move(left)), right_(std::move(right)) {}

  double Evaluate(double x, double y) override {
    return left_->Evaluate(x, y) * right_->Evaluate(x, y);
  }

 private:
  BaseNodePtr left_, right_;
};

class Pow : public BaseNode {
 public:
  Pow(BaseNodePtr left, BaseNodePtr right)
      : left_(std::move(left)), right_(std::move(right)) {}

  double Evaluate(double x, double y) override {
    return std::pow(left_->Evaluate(x, y), right_->Evaluate(x, y));
  }

 private:
  BaseNodePtr left_, right_;
};

// UNARY

class UnaryMinus : public BaseNode {
 public:
  explicit UnaryMinus(BaseNodePtr val) : val_(std::move(val)) {}

  double Evaluate(double x, double y) override { return -val_->Evaluate(x, y); }

 private:
  BaseNodePtr val_;
};

class Sin : public BaseNode {
 public:
  explicit Sin(BaseNodePtr val) : val_(std::move(val)) {}

  double Evaluate(double x, double y) override {
    return std::sin(val_->Evaluate(x, y));
  }

 private:
  BaseNodePtr val_;
};

class Cos : public BaseNode {
 public:
  explicit Cos(BaseNodePtr val) : val_(std::move(val)) {}

  double Evaluate(double x, double y) override {
    return std::cos(val_->Evaluate(x, y));
  }

 private:
  BaseNodePtr val_;
};

class Tan : public BaseNode {
 public:
  explicit Tan(BaseNodePtr val) : val_(std::move(val)) {}

  double Evaluate(double x, double y) override {
    return std::tan(val_->Evaluate(x, y));
  }

 private:
  BaseNodePtr val_;
};

class Asin : public BaseNode {
 public:
  explicit Asin(BaseNodePtr val) : val_(std::move(val)) {}

  double Evaluate(double x, double y) override {
    return std::asin(val_->Evaluate(x, y));
  }

 private:
  BaseNodePtr val_;
};

class Acos : public BaseNode {
 public:
  explicit Acos(BaseNodePtr val) : val_(std::move(val)) {}

  double Evaluate(double x, double y) override {
    return std::acos(val_->Evaluate(x, y));
  }

 private:
  BaseNodePtr val_;
};

class Atan : public BaseNode {
 public:
  explicit Atan(BaseNodePtr val) : val_(std::move(val)) {}

  double Evaluate(double x, double y) override {
    return std::acos(val_->Evaluate(x, y));
  }

 private:
  BaseNodePtr val_;
};

class Log : public BaseNode {
 public:
  explicit Log(BaseNodePtr val) : val_(std::move(val)) {}

  double Evaluate(double x, double y) override {
    return std::log(val_->Evaluate(x, y));
  }

 private:
  BaseNodePtr val_;
};

};  // namespace idn::parser::ast