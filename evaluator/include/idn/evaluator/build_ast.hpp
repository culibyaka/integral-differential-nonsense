#pragma once

#include <idn/evaluator/ast_node_base.hpp>

namespace idn::evaluator {

ast::BaseNodePtr BuildAstFromString(std::string s);

}
