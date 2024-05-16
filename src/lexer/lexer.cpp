#include "../lexer/lexer.hpp"

namespace lexer {
using namespace token;

bool is_letter(char ch) {
  return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ch == '_';
}

Lexer::Lexer(std::string input) : input(input), position(0), read_position(0) {
  this->read_char();
}

void Lexer::read_char() {
  if (this->read_position >= this->input.size()) {
    this->current_char = '\0';
  } else {
    this->current_char = this->input[this->read_position];
  }
  this->position = this->read_position++;
}

void Lexer::skip_whitespace() {
  while (this->current_char == ' ') {
    this->read_char();
  }
}

Token Lexer::next_token() {
  this->skip_whitespace();
  Token token;
  if (is_letter(this->current_char)) {
    token.literal = this->read_identifier();
  } else {
    token.literal = std::string{this->current_char};
  }
  token.infer_type();
  this->read_char();
  return token;
}

std::string Lexer::read_identifier() {
  auto start = this->position;
  while (is_letter(this->current_char)) {
    this->read_char();
  }
  return this->input.substr(start, this->position - start);
}
} // namespace lexer
