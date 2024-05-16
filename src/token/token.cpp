#include "token.hpp"
namespace token {
  Token::Token(TokenType type, std::string literal) : type(type), literal(literal)
  {};
  bool token::Token::operator==(const token::Token& other) const {
    return this->type == other.type && this->literal == other.literal;
  }
}
