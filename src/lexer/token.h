#pragma once
#include <string>



enum class TokenType {
    // Literals
    Number,
    Identifier,

    // Operators
    Plus,
    Minus,
    Star,
    Slash,
    Equals,

    // Parentheses
    LeftP,
    RightP,

    // Keywords
    Print,

    // Input end
    End
};

// Lexer output structure
struct Token { 
    TokenType type; 
    std::string lexeme;
};
const char* token_type_to_string(TokenType type);