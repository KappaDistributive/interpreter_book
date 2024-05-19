#pragma once
#include "../token/token.hpp"
#include <string>

using namespace token;

namespace lexer {
class Lexer {
public:
  std::string input;
  size_t position;      // current position in input (points to current_char)
  size_t read_position; // current readin position in input (after current_char)
  char current_char;

  Lexer(std::string input);

  void skip_whitespace();

  Token next_token();

  void read_char();

  std::string read_identifier();

  std::string read_number();
};
} // namespace lexer
