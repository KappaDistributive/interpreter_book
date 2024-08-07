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
}

TEST(Lexer, NextTokenSimple) {
  std::string input{"=+(){},;"};

  std::vector<Token> expected{
      {Token("="), Token("+"),
       Token("("), Token(")"),
       Token("{"), Token("}"),
       Token(","), Token(";"),
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
  std::string input{"let five = 5;"};

  std::vector<Token> expected{
      {Token("let"), Token("five"),
       Token("="), Token("5"),
       Token(";"), Token()}};

  Lexer lexer(input);
  for (size_t index{0}; index < expected.size(); ++index) {
    Token token = lexer.next_token();
    EXPECT_EQ(expected[index], token);
  }
  Token token = lexer.next_token();
}

TEST(Lexer, NextTokenScript) {
  std::string input{"let five = 5;\n"
                    "let ten = 10;\n"
                    "\n"
                    "let add = fn(x, y) {\n"
                    "  x + y;\n"
                    "};\n"
                    "\n"
                    "let result = add(five, ten);"};
  
  // Use explicit constructors here to test type inference
  std::vector<Token> expected{{Token(TokenType::LET, "let"),
                               Token(TokenType::INDENT, "five"),
                               Token(TokenType::ASSIGN, "="),
                               Token(TokenType::INT, "5"),
                               Token(TokenType::SEMICOLON, ";"),
                               Token(TokenType::LET, "let"),
                               Token(TokenType::INDENT, "ten"),
                               Token(TokenType::ASSIGN, "="),
                               Token(TokenType::INT, "10"),
                               Token(TokenType::SEMICOLON, ";"),
                               Token(TokenType::LET, "let"),
                               Token(TokenType::INDENT, "add"),
                               Token(TokenType::ASSIGN, "="),
                               Token(TokenType::FUNCTION, "fn"),
                               Token(TokenType::LPAREN, "("),
                               Token(TokenType::INDENT, "x"),
                               Token(TokenType::COMMA, ","),
                               Token(TokenType::INDENT, "y"),
                               Token(TokenType::RPAREN, ")"),
                               Token(TokenType::LBRACE, "{"),
                               Token(TokenType::INDENT, "x"),
                               Token(TokenType::PLUS, "+"),
                               Token(TokenType::INDENT, "y"),
                               Token(TokenType::SEMICOLON, ";"),
                               Token(TokenType::RBRACE, "}"),
                               Token(TokenType::SEMICOLON, ";"),
                               Token(TokenType::LET, "let"),
                               Token(TokenType::INDENT, "result"),
                               Token(TokenType::ASSIGN, "="),
                               Token(TokenType::INDENT, "add"),
                               Token(TokenType::LPAREN, "("),
                               Token(TokenType::INDENT, "five"),
                               Token(TokenType::COMMA, ","),
                               Token(TokenType::INDENT, "ten"),
                               Token(TokenType::RPAREN, ")"),
                               Token(TokenType::SEMICOLON, ";"),
                               Token()}};

  Lexer lexer(input);
  for (size_t index{0}; index < expected.size(); ++index) {
    Token token = lexer.next_token();
    EXPECT_EQ(expected[index], token);
  }
  Token token = lexer.next_token();
}

TEST(Lexer, NextTokenExpanded) {
  std::string input{"!*<>/-"};
  std::vector<Token> expected{{
    Token(TokenType::BANG, "!"),
    Token(TokenType::ASTERISK, "*"),
    Token(TokenType::LT, "<"),
    Token(TokenType::GT, ">"),
    Token(TokenType::SLASH, "/"),
    Token(TokenType::MINUS, "-"),
    Token(),
  }};

  Lexer lexer(input);
  EXPECT_EQ(expected.size(), input.size() + 1);
  for (size_t index{0}; index < expected.size(); ++index) {
    Token token = lexer.next_token();
    EXPECT_EQ(expected[index], token);
  }
  Token token = lexer.next_token();
}

TEST(Lexer, NextTokenControlFlow) {
  std::string input{"true false\n"
    "if else return"};
  std::vector<Token> expected{{
    Token(TokenType::TRUE, "true"),
    Token(TokenType::FALSE, "false"),
    Token(TokenType::IF, "if"),
    Token(TokenType::ELSE, "else"),
    Token(TokenType::RETURN, "return"),
    Token(),
  }};

  Lexer lexer(input);
  EXPECT_EQ(expected.size(), 6);
  for (size_t index{0}; index < expected.size(); ++index) {
    Token token = lexer.next_token();
    EXPECT_EQ(expected[index], token);
  }
  Token token = lexer.next_token();
}

TEST(Lexer, Complex) {
  std::string input{"!-/*5;\n"
    "5 < 10 > 5;\n"
    "if (5 < 10) {\n"
    "    return true;\n"
    "} else {\n"
    "    return false;\n"
    "}\n" 
    "\n"
    "10 == 10;\n"
    "10 != 9;"
  };
  std::vector<Token> expected{{
    Token(TokenType::BANG, "!"),
    Token(TokenType::MINUS, "-"),
    Token(TokenType::SLASH, "/"),
    Token(TokenType::ASTERISK, "*"),
    Token(TokenType::INT, "5"),
    Token(TokenType::SEMICOLON, ";"),
    Token(TokenType::INT, "5"),
    Token(TokenType::LT, "<"),
    Token(TokenType::INT, "10"),
    Token(TokenType::GT, ">"),
    Token(TokenType::INT, "5"),
    Token(TokenType::SEMICOLON, ";"),
    Token(TokenType::IF, "if"),
    Token(TokenType::LPAREN, "("),
    Token(TokenType::INT, "5"),
    Token(TokenType::LT, "<"),
    Token(TokenType::INT, "10"),
    Token(TokenType::RPAREN, ")"),
    Token(TokenType::LBRACE, "{"),
    Token(TokenType::RETURN, "return"),
    Token(TokenType::TRUE, "true"),
    Token(TokenType::SEMICOLON, ";"),
    Token(TokenType::RBRACE, "}"),
    Token(TokenType::ELSE, "else"),
    Token(TokenType::LBRACE, "{"),
    Token(TokenType::RETURN, "return"),
    Token(TokenType::FALSE, "false"),
    Token(TokenType::SEMICOLON, ";"),
    Token(TokenType::RBRACE, "}"),
    Token(TokenType::INT, "10"),
    Token(TokenType::EQ, "=="),
    Token(TokenType::INT, "10"),
    Token(TokenType::SEMICOLON, ";"),
    Token(TokenType::INT, "10"),
    Token(TokenType::NOT_EQ, "!="),
    Token(TokenType::INT, "9"),
    Token(TokenType::SEMICOLON, ";"),
    Token(),
  }};

  Lexer lexer(input);
  for (size_t index{0}; index < expected.size(); ++index) {
    Token token = lexer.next_token();
    EXPECT_EQ(expected[index], token);
  }
  Token token = lexer.next_token();
}

} // namespace lexer
