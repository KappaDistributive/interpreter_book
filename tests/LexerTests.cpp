#include "../src/lexer/lexer.hpp"
#include "../src/token/token.hpp"

#include <gtest/gtest.h>

#include <iostream>

namespace lexer {
using namespace token;

TEST(Lexer, NextToken) {
  std::u32string input{U"=+(){},;"};

  std::vector<Token> expected{{
      Token(TokenType::ASSIGN, U"="), Token(TokenType::PLUS, U"+"),
      Token(TokenType::LPAREN, U"("), Token(TokenType::RPAREN, U")"),
      Token(TokenType::LBRACE, U"{"), Token(TokenType::RBRACE, U"}"),
      Token(TokenType::COMMA, U","),
      Token(TokenType::SEMICOLON, U";"),
      Token(TokenType::ENDF, std::u32string{U'\0'})
  }};

  Lexer l(input);
  EXPECT_EQ(expected.size(), input.size() + 1);
  for (size_t index{0}; index < expected.size(); ++index) {
    Token token = l.next_token();
    EXPECT_EQ(expected[index], token);
  }
  Token token = l.next_token();
}
} // namespace lexer
