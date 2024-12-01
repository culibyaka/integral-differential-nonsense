#include <cstdlib>
#include <functional>
#include <idn/evaluator/parser.hpp>
#include "AST.hpp"
#include "idn/common/assert.hpp"
#include "idn/evaluator/ast_node_base.hpp"
#include "lexer.hpp"
#include <memory>
#include <optional>
#include <format>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_set>

namespace idn::parser {

static const std::unordered_set<std::string> kBuiltinFunctionNames = {
  "sin", "cos", "tan", "asin", "acos", "atan", "log"
};

static ast::BaseNodePtr CreateFunction(std::string_view function_name, ast::BaseNodePtr subexpr) {
#define F(name, cls_name) \
  if (function_name == #name) { \
    return std::make_shared<ast::cls_name>(subexpr); \
  }

  F(sin, Sin)
  F(cos, Cos)
  F(tan, Tan)
  F(asin, Asin)
  F(acos, Acos)
  F(atan, Atan)
  F(log, Log)
#undef F

  IDN_UNREACHEBLE();
}

class Parser::ParserImpl {
 public:
  explicit ParserImpl(LexerPtr lexer) : lexer_(std::move(lexer)) {}

  ast::BaseNodePtr Parse() { return ParseExpr(); }

 private:
  ast::BaseNodePtr ParseExpr();

  Token Eat(TokenKind kind);
  [[noreturn]] void Error(std::string msg) noexcept(false);

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

void Parser::ParserImpl::Error(std::string message) {
  // TODO: make nice error message
  throw std::runtime_error(message);
}

ast::BaseNodePtr Parser::ParserImpl::ParseExpr() {
  auto tok = lexer_->Lex();
  if (tok->Is(TokenKind::kName)) {
    if (tok->text_ == "x") {
      return ast::GetX();
    } else if (tok->text_ == "y") {
      return ast::GetY();
    } else if (kBuiltinFunctionNames.contains(tok->text_)) {
      const auto subexpr = ParseExpr();
      return CreateFunction(tok->text_, subexpr);
    } else {
      Error(std::format("Expected x, y or function name, but got {}", tok->text_));
    }
  } else if (tok->Is(TokenKind::kNumber)) {
    // FIXME: use modern cpp
    const auto value = std::stod(tok->text_);
    return std::make_shared<ast::Const>(value);
  } else if (tok->kind_ == TokenKind::kLPar) {
    const auto lhs = ParseExpr();
    const auto op = lexer_->Lex();
    if (!op->IsOneOf(TokenKind::kPlus, TokenKind::kMinus, TokenKind::kDivide, TokenKind::kMultiply)) {
      Error("invalid operation");
    }
    const auto rhs = ParseExpr();
    Eat(TokenKind::kRPar);

    switch (op->kind_) {
    case TokenKind::kPlus:
      return std::make_shared<ast::Plus>(lhs, rhs);
    case TokenKind::kMinus:
      return std::make_shared<ast::Minus>(lhs, rhs);
    case TokenKind::kDivide:
      return std::make_shared<ast::Divide>(lhs, rhs);
    case TokenKind::kMultiply:
      return std::make_shared<ast::Multiply>(lhs, rhs);
    default:
      IDN_UNREACHEBLE();
    }
  }

  Error("invalid expression");
}

// IMPL

Parser::Parser(LexerPtr lexer) noexcept
  : impl_(std::make_unique<Parser::ParserImpl>(std::move(lexer))) {}

Parser::~Parser() = default;

ast::BaseNodePtr Parser::Parse() {
  return impl_->Parse();
}

}