#pragma once
#include <string_view>
#include "lexer/token.h"

class Lexer{
    public:
        // Constructs the lexer with source code
        explicit Lexer(std::string_view src);

        // Returns next token from the input
        Token next_token();

    private:
        char peek() const; // Looks at current character
        char advance(); // Consumes current character
        bool is_at_end() const; // Checks if the input is finished

        void skip_whitespace();

        Token lex_number();
        Token lex_identifier();

    private:
        std::string_view source; // Reference to the source text
        size_t position = 0; // Current position in the source

};
