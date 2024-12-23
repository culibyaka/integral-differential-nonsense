#include <idn/evaluator/ast_node_base.hpp>
#include <idn/evaluator/capi.hpp>

extern "C" float idn_parser_function_ctx_call(void* ctx, float x,
                                               float y) {
  auto func = *reinterpret_cast<idn::evaluator::ast::BaseNodePtr*>(ctx);
  return func->Evaluate(x, y);
}
