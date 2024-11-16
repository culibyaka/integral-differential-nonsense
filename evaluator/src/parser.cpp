#include <idn/evaluator/parser.hpp>
#include "lexer.hpp"
#include <idn/evaluator/AST.hpp>
#include <memory>
#include <optional>
#include <stdexcept>

namespace idn::parser {

class Parser::ParserImpl {
 public:
  explicit ParserImpl(LexerPtr lexer) : lexer_(std::move(lexer)) {}

  ast::BaseNodePtr Parse();

 private:
  ast::BaseNodePtr ParseExpr() { return {}; }

  Token Eat(TokenKind kind);

 private:
  LexerPtr lexer_;
};

Token Parser::ParserImpl::Eat(TokenKind kind) {
  const auto token = lexer_->Lex();
  if (!token.has_value()) {
    throw std::runtime_error("no token");
  }
  if (token->kind_ != kind) {
    // FIXME: make separete function for this
    // FIXME: use SyntaxError class
    // FIXME: more useful error message
    throw std::runtime_error("Syntax error");
  }
  return *token;
}

// IMPL

Parser::Parser(LexerPtr lexer) noexcept
  : impl_(std::make_unique<ParserImpl>(std::move(lexer))) {}

ast::BaseNodePtr Parser::Parse() {
  return impl_->Parse();
}

}