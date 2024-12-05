#include <idn/evaluator/build_ast.hpp>
#include <memory>
#include "idn/evaluator/parser.hpp"
#include "lexer.hpp"

namespace idn::evaluator {

parser::ast::BaseNodePtr BuildAstFromString(std::string s) {
  auto lexer = std::make_unique<idn::parser::Lexer>(s);
  auto parser = std::make_unique<parser::Parser>(std::move(lexer));
  return parser->Parse();
}

}
