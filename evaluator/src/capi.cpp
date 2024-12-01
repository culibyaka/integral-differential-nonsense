#include <idn/evaluator/ast_node_base.hpp>
#include <idn/evaluator/capi.hpp>

extern "C" double idn_parser_function_ctx_call(function_ctx ctx, double x,
                                               double y) {
  return ctx.func_->Evaluate(x, y);
}
