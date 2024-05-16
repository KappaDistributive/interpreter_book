#include "token.hpp"

namespace token {

Token::Token() : type(TokenType::ENDF), literal(std::string{'\0'}) {};

Token::Token(TokenType type, std::string literal)
    : type(type), literal(literal) {};

bool Token::operator==(const token::Token &other) const {
  return this->type == other.type && this->literal == other.literal;
}

std::ostream &operator<<(std::ostream &os, const TokenType &type) {
  switch (type) {
  case TokenType::ILLEGAL:
    os << "ILLEGAL";
    break;
  case TokenType::ENDF:
    os << "EOF";
    break;
  case TokenType::INDENT:
    os << "IDENTIFIER";
    break;
  case TokenType::INT:
    os << "INT";
    break;
  case TokenType::ASSIGN:
    os << "ASSIGN";
    break;
  case TokenType::PLUS:
    os << "PLUS";
    break;
  case TokenType::COMMA:
    os << "COMMA";
    break;
  case TokenType::SEMICOLON:
    os << "SEMICOLON";
    break;
  case TokenType::LPAREN:
    os << "LPAREN";
    break;
  case TokenType::RPAREN:
    os << "RPAREN";
    break;
  case TokenType::LBRACE:
    os << "LBRACE";
    break;
  case TokenType::RBRACE:
    os << "RBRACE";
    break;
  case TokenType::FUNCTION:
    os << "FUNCTION";
    break;
  case TokenType::LET:
    os << "LET";
    break;
  }
  return os;
}

std::ostream &operator<<(std::ostream &os, const Token &token) {
  os << token.type;
  if (token.type == TokenType::INDENT || token.type == TokenType::INT) {
    os << '(' << token.literal << ')';
  }
  return os;
}

void Token::infer_type() {
  if (this->literal == std::string{'\0'}) {
    this->type = TokenType::ENDF;
  } else if (this->literal == "=") {
    this->type = TokenType::ASSIGN;
  } else if (this->literal == "(") {
    this->type = TokenType::LPAREN;
  } else if (this->literal == ")") {
    this->type = TokenType::RPAREN;
  } else if (this->literal == "{") {
    this->type = TokenType::LBRACE;
  } else if (this->literal == "}") {
    this->type = TokenType::RBRACE;
  } else if (this->literal == "+") {
    this->type = TokenType::PLUS;
  } else if (this->literal == ",") {
    this->type = TokenType::COMMA;
  } else if (this->literal == ";") {
    this->type = TokenType::SEMICOLON;
  } else if (this->literal == "let") {
    this->type = TokenType::LET;
  } else if (std::all_of(this->literal.cbegin(), this->literal.cend(),
                         ::isdigit)) {
    this->type = TokenType::INT;
  } else if (this->literal.size() > 0 && this->literal != std::string{'\0'}) {
    this->type = TokenType::INDENT;
  }
}
} // namespace token
