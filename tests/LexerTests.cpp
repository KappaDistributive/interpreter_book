#include "../src/lexer/lexer.hpp"
#include "../src/token/token.hpp"

#include <gtest/gtest.h>

namespace lexer {
using namespace token;

TEST(Lexer, NextToken) {
  std::string input{"=+(){},;"};

  std::vector<Token> expected{{
      Token(TokenType::ASSIGN, "="), Token(TokenType::PLUS, "+"),
      Token(TokenType::LPAREN, "("), Token(TokenType::RPAREN, ")"),
      Token(TokenType::LBRACE, "{"), Token(TokenType::RBRACE, "}"),
      Token(TokenType::COMMA, ","),
      Token(TokenType::SEMICOLON, ";"),
      Token()
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
