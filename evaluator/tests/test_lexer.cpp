#include <gtest/gtest.h>
#include "lexer.hpp"

TEST(Lexer, Basic) {
  idn::parser::Lexer lexer("       (1**asd");
  EXPECT_FALSE(lexer.IsEnd());
  EXPECT_TRUE(lexer.Lex()->Is(idn::parser::TokenKind::kLPar));

  EXPECT_FALSE(lexer.IsEnd());
  EXPECT_TRUE(lexer.Lex()->Is(idn::parser::TokenKind::kNumber));

  EXPECT_FALSE(lexer.IsEnd());
  EXPECT_TRUE(lexer.Lex()->Is(idn::parser::TokenKind::kMultiply));

  EXPECT_FALSE(lexer.IsEnd());
  EXPECT_TRUE(lexer.Lex()->Is(idn::parser::TokenKind::kMultiply));


  EXPECT_FALSE(lexer.IsEnd());
  EXPECT_TRUE(lexer.Lex()->Is(idn::parser::TokenKind::kName));

  EXPECT_TRUE(lexer.IsEnd());
}
