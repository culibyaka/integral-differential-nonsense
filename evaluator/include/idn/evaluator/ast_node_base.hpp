#pragma once

#include <memory>

namespace idn::evaluator::ast {

class BaseNode {
 public:
  double operator()(double x, double y) { return Evaluate(x, y); }
  virtual double Evaluate(double x, double y) = 0;
  virtual ~BaseNode() = default;
};

using BaseNodePtr = std::shared_ptr<BaseNode>;

}  // namespace idn::parser::ast