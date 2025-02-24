#pragma once
#include <cstdint>
#include <idn/common/assert.hpp>
#include <optional>
#include <string>

namespace idn::evaluator {

enum class TokenKind : std::uint32_t {
  kNumber = 0,
  kLPar,
  kRPar,
  kPlus,
  kMinus,
  kMultiply,
  kDivide,
  kName,
  kEof
};

struct Location {
  std::size_t pos_;
};

struct Token {
  TokenKind kind_;
  Location loc_;
  std::string text_;
  //std::string_view text_;

  bool Is(TokenKind kind) const { return kind_ == kind; }
  bool IsOneOf(TokenKind k1, TokenKind k2) const {
    return Is(k1) || Is(k2);
  }
  template<typename ...Ts>
  bool IsOneOf(TokenKind kind, Ts... ks) const {
    return Is(kind) || IsOneOf(ks...);
  }
};

std::string ToString(TokenKind kind);

class Lexer {
 public:
  explicit Lexer(std::string_view s) : text_(s), pos_(0) {}

  bool IsEnd() const noexcept { return pos_ >= text_.size(); }

  std::optional<Token> Lex() noexcept;

 private:
  // FIXME
  char Peek() const noexcept {
    IDN_ASSERT(pos_ < text_.size());
    return text_[pos_];
  }

  char Next() noexcept { return text_[pos_++]; }

  Token LexNumber() noexcept;
  Token LexName() noexcept;

  void SkipSpaces() noexcept;
  Location GetCurrentLocation() const noexcept { return {.pos_ = pos_}; }

 private:
  std::string text_;
  std::size_t pos_;
};

}  // namespace idn::parser
