#include "token.hpp"
#include <algorithm>

namespace token {

Token::Token() noexcept : type(TokenType::ENDF), literal(std::string{'\0'}) {};

Token::Token(TokenType type, std::string literal) noexcept
    : type(type), literal(literal) {};

Token::Token(std::string literal) noexcept : literal(literal) {
  this->infer_type();
}

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
  case TokenType::MINUS:
    os << "MINUS";
    break;
  case TokenType::BANG:
    os << "BANG";
    break;
  case TokenType::SLASH:
    os << "SLASH";
    break;
  case TokenType::ASTERISK:
    os << "ASTERISK";
    break;
  case TokenType::LT:
    os << "LT";
    break;
  case TokenType::GT:
    os << "GT";
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
  case TokenType::TRUE:
    os << "TRUE";
    break;
  case TokenType::FALSE:
    os << "FALSE";
    break;
  case TokenType::IF:
    os << "IF";
    break;
  case TokenType::ELSE:
    os << "ELSE";
    break;
  case TokenType::RETURN:
    os << "RETURN";
    break;
  case TokenType::EQ:
    os << "EQ";
    break;
  case TokenType::NOT_EQ:
    os << "NOT_EQ";
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
  const auto literal = this->literal;
  if (literal == std::string{'\0'}) {
    this->type = TokenType::ENDF;
  } else if (auto search = std::find_if(
                 symbol_map.cbegin(), symbol_map.cend(),
                 [literal](
                     std::pair<std::string_view, TokenType> const &candidate) {
                   return candidate.first == literal;
                 });
             search != symbol_map.cend()) {
    this->type = search->second;
  } else if (std::all_of(literal.cbegin(), literal.cend(), ::isdigit)) {
    this->type = TokenType::INT;
  } else if (literal.size() > 0 && literal != std::string{'\0'}) {
    this->type = TokenType::INDENT;
  } else {
    this->type = TokenType::ILLEGAL;
  }
}
} // namespace token
