#include "lexer/lexer.h"
#include <cctype>
// Constructor
Lexer::Lexer(std::string_view src) : source(src) {}

// Looks at current character
char Lexer::peek() const {
    if(is_at_end()) return '\0';
    return source[position];
}

// Consumes current character
char Lexer::advance(){
    return source[position++];
}
// End of input check
bool Lexer::is_at_end() const{
    return position >= source.size();
}

// Skip whitespaces
void Lexer::skip_whitespace() {
    while(!is_at_end() && std::isspace(peek())){
        advance();
    }
}

// Lexer entry point

Token Lexer::next_token(){
    skip_whitespace();

    if (is_at_end()) {
        return { TokenType::End, ""};
    }
    char c = advance();

    // Tokens of single character
    switch(c) {
        case '+': return { TokenType::Plus, "+"};
        case '-': return { TokenType::Minus, "-"};
        case '*': return { TokenType::Star, "*"};
        case '/': return { TokenType::Slash, "/"};
        case '=': return { TokenType::Equals, "="};
        case '(': return { TokenType::LeftP, "("};
        case ')': return { TokenType::RightP, ")"};
    }
    // Number literals
    if (std::isdigit(c)) {
        position--; // Since one digit has already been consumed
        return lex_number();
    }
    // Identifiers or keywords
    if (std::isalpha(c) || c == '_'){
        position--;
        return lex_identifier();
    }
    // Unknown character
    return { TokenType::End, ""};
}

Token Lexer::lex_number(){
    size_t start = position;
    while(!is_at_end() && std::isdigit(peek())){
        advance();
    }

    return {
        TokenType::Number,
        std::string(source.substr(start, position - start))
    };

}

Token Lexer::lex_identifier() {
    size_t start = position;
    while(!is_at_end() && (std::isalnum(peek()) || peek() == '_')){
        advance();
    }
    std::string text(source.substr(start, position - start));

    if (text == "print"){
        return {
        TokenType::Print,
        text
    };
    }
    return {
        TokenType::Identifier,
        text
    };
    
}
const char* token_type_to_string(TokenType type) {
    switch (type) {
        case TokenType::Identifier: return "Identifier";
        case TokenType::Number:     return "Number";
        case TokenType::Plus:       return "Plus";
        case TokenType::Minus:      return "Minus";
        case TokenType::Star:       return "Star";
        case TokenType::Slash:      return "Slash";
        case TokenType::Equals:     return "Equals";
        case TokenType::LeftP:     return "LeftP";
        case TokenType::RightP:     return "RightP";
        case TokenType::Print:      return "Print";
        case TokenType::End:        return "End";
        default:                    return "Unknown";
    }
}