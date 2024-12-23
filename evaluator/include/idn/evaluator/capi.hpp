#pragma once
#include <idn/evaluator/ast_node_base.hpp>

extern "C" {

// FIXME: add calling convention specifier
// NOLINTNEXTLINE
float idn_parser_function_ctx_call(void* ctx, float x, float y);
}
