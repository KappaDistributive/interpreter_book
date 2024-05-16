#pragma once
#include <iostream>
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

  std::ostream& operator<<(std::ostream&, const TokenType&);
  
  class Token {
    public:
      TokenType type;
      std::string literal;

      Token();

      Token(TokenType, std::string);

      void infer_type();

      bool operator==(const Token&) const;

      friend std::ostream& operator<<(std::ostream&, const Token&);
  };
}
