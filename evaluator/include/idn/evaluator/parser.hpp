#pragma once

#include <memory>
#include "AST.hpp"

namespace idn::parser {

class Lexer;
class Token;

class Parser {
  using LexerPtr = std::unique_ptr<Lexer>;

 public:
  explicit Parser(LexerPtr lexer) noexcept;

  ast::BaseNodePtr Parse();

 private:
  class ParserImpl;
  
  // TODO: not use PImpl???
  std::unique_ptr<ParserImpl> impl_;
};

}  // namespace idn::parser