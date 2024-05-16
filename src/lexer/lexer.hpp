#pragma once
#include <string>
#include "../token/token.hpp"

namespace lexer {
  class Lexer {
    public:
      Lexer(std::string input);
      token::Token next_token();
  };
}
