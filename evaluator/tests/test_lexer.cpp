#include <gtest/gtest.h>
#include "lexer.hpp"

TEST(Lexer, Basic) {
  idn::evaluator::Lexer lexer("       (1**asd");
  EXPECT_FALSE(lexer.IsEnd());
  EXPECT_TRUE(lexer.Lex()->Is(idn::evaluator::TokenKind::kLPar));

  EXPECT_FALSE(lexer.IsEnd());
  EXPECT_TRUE(lexer.Lex()->Is(idn::evaluator::TokenKind::kNumber));

  EXPECT_FALSE(lexer.IsEnd());
  EXPECT_TRUE(lexer.Lex()->Is(idn::evaluator::TokenKind::kMultiply));

  EXPECT_FALSE(lexer.IsEnd());
  EXPECT_TRUE(lexer.Lex()->Is(idn::evaluator::TokenKind::kMultiply));


  EXPECT_FALSE(lexer.IsEnd());
  EXPECT_TRUE(lexer.Lex()->Is(idn::evaluator::TokenKind::kName));

  EXPECT_TRUE(lexer.IsEnd());
}
