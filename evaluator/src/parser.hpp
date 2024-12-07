#pragma once

#include <memory>
#include <idn/evaluator/ast_node_base.hpp>
#include "lexer.hpp"

namespace idn::evaluator {

class Lexer;
class Token;
// enum TokenKind;

class Parser {
  using LexerPtr = std::unique_ptr<Lexer>;
 public:
  explicit Parser(LexerPtr lexer) : lexer_(std::move(lexer)) {}

  ast::BaseNodePtr Parse() { return ParseExpr(); }

 private:
  ast::BaseNodePtr ParseExpr();

  Token Eat(TokenKind kind);
  [[noreturn]] void Error(std::string msg) noexcept(false);

 private:
  LexerPtr lexer_;
};


}  // namespace idn::parser