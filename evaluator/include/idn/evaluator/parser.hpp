#pragma once

#include <memory>
#include <idn/evaluator/ast_node_base.hpp>

namespace idn::parser {

class Lexer;
class Token;

class Parser {
  using LexerPtr = std::unique_ptr<Lexer>;

 public:
  explicit Parser(LexerPtr lexer) noexcept;
  ~Parser();

  ast::BaseNodePtr Parse();

 private:
  class ParserImpl;
  
  // TODO: not use PImpl???
  std::unique_ptr<ParserImpl> impl_;
};

}  // namespace idn::parser