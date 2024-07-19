#pragma once
#include <array>
#include <iostream>
#include <string>

namespace token {

template <typename T, std::size_t m, std::size_t n>
constexpr std::array<T, m + n> concat(std::array<T, m> lhs,
                                      std::array<T, n> rhs) {
  std::array<T, m + n> result{};
  std::size_t index{0};
  for (auto &el : lhs) {
    result[index++] = std::move(el);
  }
  for (auto &el : rhs) {
    result[index++] = std::move(el);
  }
  return result;
}

enum TokenType : int {
  ILLEGAL,
  ENDF,
  INDENT,
  INT,
  ASSIGN,
  PLUS,
  MINUS,
  BANG,
  ASTERISK,
  SLASH,
  LT,
  GT,
  COMMA,
  SEMICOLON,
  LPAREN,
  RPAREN,
  LBRACE,
  RBRACE,
  FUNCTION,
  LET,
  TRUE,
  FALSE,
  IF,
  ELSE,
  RETURN,
  EQ,
  NOT_EQ
};

constexpr std::array<std::pair<std::string_view, TokenType>, 16>
    special_symbols{{
        {"=", TokenType::ASSIGN},
        {"+", TokenType::PLUS},
        {"-", TokenType::MINUS},
        {"!", TokenType::BANG},
        {"*", TokenType::ASTERISK},
        {"/", TokenType::SLASH},
        {"<", TokenType::LT},
        {">", TokenType::GT},
        {",", TokenType::COMMA},
        {";", TokenType::SEMICOLON},
        {"(", TokenType::LPAREN},
        {")", TokenType::RPAREN},
        {"{", TokenType::LBRACE},
        {"}", TokenType::RBRACE},
        {"==", TokenType::EQ},
        {"!=", TokenType::NOT_EQ},
    }};

constexpr std::array<std::pair<std::string_view, TokenType>, 7> keywords{{
    {"fn", TokenType::FUNCTION},
    {"let", TokenType::LET},
    {"true", TokenType::TRUE},
    {"false", TokenType::FALSE},
    {"if", TokenType::IF},
    {"else", TokenType::ELSE},
    {"return", TokenType::RETURN},
}};

constexpr auto symbol_map = concat(special_symbols, keywords);

std::ostream &operator<<(std::ostream &, const TokenType &);

class Token {
public:
  TokenType type;
  std::string literal;

  Token() noexcept;

  Token(TokenType, std::string) noexcept;

  Token(std::string) noexcept;

  void infer_type();

  bool operator==(const Token &) const;

  friend std::ostream &operator<<(std::ostream &, const Token &);
};
} // namespace token
