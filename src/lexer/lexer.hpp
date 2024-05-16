#pragma once
#include <string>
#include "../token/token.hpp"

using namespace token;

namespace lexer {
  class Lexer {
    public:
      std::u32string input;
      size_t position;  // current position in input (points to current_char)
      size_t read_position;  // current readin position in input (after current_char)
      char32_t current_char;

      Lexer(std::u32string input);

      Token next_token();

      void read_char();
  };
}
