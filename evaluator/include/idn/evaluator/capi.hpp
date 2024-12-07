#pragma once
#include <idn/evaluator/ast_node_base.hpp>

extern "C" {

// NOLINTNEXTLINE
struct function_ctx {
  idn::evaluator::ast::BaseNodePtr func_;
};

// FIXME: add calling convention specifier
// NOLINTNEXTLINE
double idn_parser_function_ctx_call(function_ctx ctx, double x, double y);
}
