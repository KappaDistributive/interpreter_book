#include "../lexer/lexer.hpp"

namespace lexer {
  Lexer::Lexer(std::string input) {}

  token::Token Lexer::next_token() {
    return token::Token(token::TokenType::INT, "");
  }
}
