#include "../src/token/token.hpp"
#include "../src/lexer/lexer.hpp"

#include <gtest/gtest.h>

namespace lexer {
using namespace token;

TEST(Lexer, NextToken) {
  std::string input{"=+(){},;"};

  std::vector<Token> expected{
      {Token(TokenType::ASSIGN, "="), Token(TokenType::PLUS, "+"),
       Token(TokenType::LPAREN, "("), Token(TokenType::RPAREN, ")"),
       Token(TokenType::LBRACE, "{"), Token(TokenType::RBRACE, "}"),
       Token(TokenType::COMMA, ","), Token(TokenType::SEMICOLON, ";")}};

  Lexer l(input);
  for (size_t index{0}; index < input.size(); ++index) {
    auto token = l.next_token();
    EXPECT_EQ(expected[index], token);
  }
}
} // namespace lexer
