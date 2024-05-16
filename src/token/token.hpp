#pragma once
#include <string>

namespace token {
  enum TokenType: int {
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
  
  class Token {
    public:
      TokenType type;
      std::string literal;

      Token(TokenType type, std::string literal);

      bool operator==(const Token& other) const;
  };
}
