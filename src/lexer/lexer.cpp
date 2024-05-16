#include "../lexer/lexer.hpp"

namespace lexer {
using namespace token;

Lexer::Lexer(std::u32string input) : input(input) {
  this->read_char();
}

void Lexer::read_char() {
  if (this->read_position >= this->input.size()) {
    this->current_char = U'\0';
  } else {
    this->current_char = this->input[this->read_position];
  }
  this->position = this->read_position++;
}

Token Lexer::next_token() {
  Token token;
  token.literal = std::u32string{this->current_char};
  token.infer_type();
  this->read_char();
  return token;
}
} // namespace lexer
