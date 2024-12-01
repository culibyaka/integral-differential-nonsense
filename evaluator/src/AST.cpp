#include "AST.hpp"
#include <memory>
#include "idn/evaluator/ast_node_base.hpp"

namespace idn::parser::ast {

BaseNodePtr GetX() {
  static X global_x;
  return std::shared_ptr<X>(std::shared_ptr<void>(), &global_x);
}

BaseNodePtr GetY() {
  static Y global_y;
  return std::shared_ptr<Y>(std::shared_ptr<void>(), &global_y);
}

}  // namespace idn::parser::ast
