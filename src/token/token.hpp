#pragma once
#include <iostream>
#include <map>
#include <string>

namespace token {
enum TokenType : int {
  ILLEGAL,
  ENDF,
  INDENT,
  INT,
  ASSIGN,
  PLUS,
  COMMA,
  SEMICOLON,
  LPAREN,
  RPAREN,
  LBRACE,
  RBRACE,
  FUNCTION,
  LET
};

static const std::map<std::string, TokenType> keywords{{
    std::pair("fn", TokenType::FUNCTION),
    std::pair("let", TokenType::LET),
}};

std::ostream &operator<<(std::ostream &, const TokenType &);

class Token {
public:
  TokenType type;
  std::string literal;

  Token() noexcept;

  Token(TokenType, std::string) noexcept;

  Token(std::string) noexcept;

  void infer_type();

  bool operator==(const Token &) const;

  friend std::ostream &operator<<(std::ostream &, const Token &);
};
} // namespace token
