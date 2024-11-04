#include "lexer.hpp"
#include <bits/ranges_util.h>
#include <cctype>
#include <idn/common/assert.hpp>

namespace idn::parser {

static const std::string kKindToString[] = {"kNumber", "kLPar",  "kRPar",
                                            "kPlus",   "kMinus", "kMultiply",
                                            "kDivide", "kName",  "kEof"};

static_assert(sizeof(kKindToString) / sizeof(kKindToString[0]) ==
                  static_cast<std::uint32_t>(TokenKind::kEof) + 1,
              "NOT MATCH");

std::string ToString(TokenKind kind) {
  IDN_ASSERT(kind <= TokenKind::kEof);
  const int idx = static_cast<std::uint32_t>(kind);
  return kKindToString[idx];
}

std::optional<Token> Lexer::Lex() noexcept {
  while (!IsEnd()) {
    SkipSpaces();

    if (std::isdigit(Peek()) > 0) {
      return LexNumber();
    }

    if (std::isalpha(Peek()) > 0) {
      return LexName();
    }

    if (Peek() == '(') {
      const auto loc = GetCurrentLocation();
      const auto str = text_.substr(pos_++, 1);
      return Token{TokenKind::kLPar, loc, str};
    }

    if (Peek() == ')') {
      const auto loc = GetCurrentLocation();
      const auto str = text_.substr(pos_++, 1);
      return Token{TokenKind::kRPar, loc, str};
    }

    if (Peek() == '+') {
      const auto loc = GetCurrentLocation();
      const auto str = text_.substr(pos_++, 1);
      return Token{TokenKind::kPlus, loc, str};
    }

    if (Peek() == '-') {
      const auto loc = GetCurrentLocation();
      const auto str = text_.substr(pos_++, 1);
      return Token{TokenKind::kMinus, loc, str};
    }

    if (Peek() == '*') {
      const auto loc = GetCurrentLocation();
      const auto str = text_.substr(pos_++, 1);
      return Token{TokenKind::kMultiply, loc, str};
    }

    if (Peek() == '/') {
      const auto loc = GetCurrentLocation();
      const auto str = text_.substr(pos_++, 1);
      return Token{TokenKind::kDivide, loc, str};
    }
  }

  return Token{TokenKind::kEof, GetCurrentLocation(), ""};
}

Token Lexer::LexNumber() noexcept {
  const auto start_loc = GetCurrentLocation();
  const auto str_start = pos_;

  while (!IsEnd() && (std::isdigit(Peek()) != 0)) {
    ++pos_;
  }

  return Token{TokenKind::kNumber, start_loc,
               text_.substr(str_start, pos_ - str_start)};
}

Token Lexer::LexName() noexcept {
  const auto start_loc = GetCurrentLocation();
  const auto str_start = pos_;

  while (!IsEnd() && (std::isalpha(Peek()) != 0)) {
    ++pos_;
  }

  return Token{TokenKind::kName, start_loc,
               text_.substr(str_start, pos_ - str_start)};
}

void Lexer::SkipSpaces() noexcept {
  while (!IsEnd() && (std::isspace(Peek()) != 0)) {
    pos_++;
  }
}

}  // namespace idn::parser
