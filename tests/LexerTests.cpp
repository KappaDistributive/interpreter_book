#include "../src/lexer/lexer.hpp"
#include "../src/token/token.hpp"

#include <gtest/gtest.h>

namespace lexer {
using namespace token;

TEST(Lexer, NextTokenAssign) {
  std::string input{"="};
  std::vector<Token> expected{{Token(TokenType::ASSIGN, "="), Token()}};

  Lexer lexer(input);
  EXPECT_EQ(expected.size(), input.size() + 1);
  for (size_t index{0}; index < expected.size(); ++index) {
    Token token = lexer.next_token();
    EXPECT_EQ(expected[index], token);
  }
  Token token = lexer.next_token();
}

TEST(Lexer, NextTokenSimple) {
  std::string input{"=+(){},;"};

  std::vector<Token> expected{
      {Token(TokenType::ASSIGN, "="), Token(TokenType::PLUS, "+"),
       Token(TokenType::LPAREN, "("), Token(TokenType::RPAREN, ")"),
       Token(TokenType::LBRACE, "{"), Token(TokenType::RBRACE, "}"),
       Token(TokenType::COMMA, ","), Token(TokenType::SEMICOLON, ";"),
       Token()}};

  Lexer lexer(input);
  EXPECT_EQ(expected.size(), input.size() + 1);
  for (size_t index{0}; index < expected.size(); ++index) {
    Token token = lexer.next_token();
    EXPECT_EQ(expected[index], token);
  }
  Token token = lexer.next_token();
  EXPECT_EQ(Token(), token);
}

TEST(Lexer, NextTokenLet) {
  std::string input{"let"};

  std::vector<Token> expected{{Token(TokenType::LET, "let"), Token()}};

  Lexer lexer(input);
  EXPECT_EQ(expected.size(), 2);
  for (size_t index{0}; index < expected.size(); ++index) {
    Token token = lexer.next_token();
    EXPECT_EQ(expected[index], token);
  }
  Token token = lexer.next_token();
}

} // namespace lexer
