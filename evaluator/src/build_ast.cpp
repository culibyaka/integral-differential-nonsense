#include <idn/evaluator/build_ast.hpp>
#include <memory>
#include "parser.hpp"
#include "lexer.hpp"

namespace idn::evaluator {

ast::BaseNodePtr BuildAstFromString(std::string s) {
  auto lexer = std::make_unique<Lexer>(s);
  auto parser = std::make_unique<Parser>(std::move(lexer));
  return parser->Parse();
}

}
