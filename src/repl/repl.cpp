#include "repl.hpp"
#include "../lexer/lexer.hpp"
#include <format>
#include <iostream>

namespace repl {
void start() {
  std::string line;
  while (true) {
    std::cout << std::format("{}", repl::prompt);
    std::getline(std::cin, line);
    token::Token tokenizer(line);
    lexer::Lexer lexer{line};
    token::Token token;
    do {
      token = lexer.next_token();
      std::cout << token << std::endl;
    } while (token.type != token::TokenType::ENDF);
  }
}
} // namespace repl
