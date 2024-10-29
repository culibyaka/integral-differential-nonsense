#pragma once

#include <cmath>
#include <memory>
#include "common.hpp"

namespace idn::parser::ast {

class BaseNode {
 public:
  double operator()(double x) { return Evaluate(x); }
  virtual double Evaluate(double x) = 0;
  virtual ~BaseNode() = default;
};

using BaseNodePtr = std::unique_ptr<BaseNode>;

// SPECIAL

class Id : public BaseNode {
 public:
  double Evaluate(double x) override { return x; }
};

class Const : public BaseNode {
 public:
  explicit Const(double value) : value_(value) {}

  double Evaluate(double x) override {
    IGNORE(x);
    return value_;
  }

 private:
  const double value_;
};

// BINARY

class Plus : public BaseNode {
 public:
  Plus(BaseNodePtr left, BaseNodePtr right)
      : left_(std::move(left)), right_(std::move(right)) {}

  double Evaluate(double x) override {
    return left_->Evaluate(x) + right_->Evaluate(x);
  }

 private:
  BaseNodePtr left_, right_;
};

class Minus : public BaseNode {
 public:
  Minus(BaseNodePtr left, BaseNodePtr right)
      : left_(std::move(left)), right_(std::move(right)) {}

  double Evaluate(double x) override {
    return left_->Evaluate(x) - right_->Evaluate(x);
  }

 private:
  BaseNodePtr left_, right_;
};

class Multiply : public BaseNode {
 public:
  Multiply(BaseNodePtr left, BaseNodePtr right)
      : left_(std::move(left)), right_(std::move(right)) {}

  double Evaluate(double x) override {
    return left_->Evaluate(x) * right_->Evaluate(x);
  }

 private:
  BaseNodePtr left_, right_;
};

class Divide : public BaseNode {
 public:
  Divide(BaseNodePtr left, BaseNodePtr right)
      : left_(std::move(left)), right_(std::move(right)) {}

  double Evaluate(double x) override {
    return left_->Evaluate(x) * right_->Evaluate(x);
  }

 private:
  BaseNodePtr left_, right_;
};

class Pow : public BaseNode {
 public:
  Pow(BaseNodePtr left, BaseNodePtr right)
      : left_(std::move(left)), right_(std::move(right)) {}

  double Evaluate(double x) override {
    return std::pow(left_->Evaluate(x), right_->Evaluate(x));
  }

 private:
  BaseNodePtr left_, right_;
};

// UNARY

class UnaryMinus : public BaseNode {
 public:
  explicit UnaryMinus(BaseNodePtr val) : val_(std::move(val)) {}

  double Evaluate(double x) override { return -val_->Evaluate(x); }

 private:
  BaseNodePtr val_;
};

class Sin : public BaseNode {
 public:
  explicit Sin(BaseNodePtr val) : val_(std::move(val)) {}

  double Evaluate(double x) override { return std::sin(val_->Evaluate(x)); }

 private:
  BaseNodePtr val_;
};

class Cos : public BaseNode {
 public:
  explicit Cos(BaseNodePtr val) : val_(std::move(val)) {}

  double Evaluate(double x) override { return std::cos(val_->Evaluate(x)); }

 private:
  BaseNodePtr val_;
};

class Tan : public BaseNode {
 public:
  explicit Tan(BaseNodePtr val) : val_(std::move(val)) {}

  double Evaluate(double x) override { return std::tan(val_->Evaluate(x)); }

 private:
  BaseNodePtr val_;
};

class Asin : public BaseNode {
 public:
  explicit Asin(BaseNodePtr val) : val_(std::move(val)) {}

  double Evaluate(double x) override { return std::asin(val_->Evaluate(x)); }

 private:
  BaseNodePtr val_;
};

class Acos : public BaseNode {
 public:
  explicit Acos(BaseNodePtr val) : val_(std::move(val)) {}

  double Evaluate(double x) override { return std::acos(val_->Evaluate(x)); }

 private:
  BaseNodePtr val_;
};

class Log : public BaseNode {
 public:
  explicit Log(BaseNodePtr val) : val_(std::move(val)) {}

  double Evaluate(double x) override { return std::log(val_->Evaluate(x)); }

 private:
  BaseNodePtr val_;
};

}  // namespace idn::parser::ast