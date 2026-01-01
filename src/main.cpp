#include <iostream>
#include "lexer/lexer.h"

const char* token_type_to_string(TokenType type);

int main() {
    Lexer lexer("x = 3 + 4 * (2-1)\nprint x");

    while (true) {
    Token t = lexer.next_token();
    std::cout << token_type_to_string(t.type)
              << " : '" << t.lexeme << "'\n";

    if (t.type == TokenType::End)
        break;
}

}
const char* token_type_to_string(TokenType type) {
    switch (type) {
        case TokenType::Number:     return "Number";
        case TokenType::Identifier: return "Identifier";
        case TokenType::Plus:       return "Plus";
        case TokenType::Minus:      return "Minus";
        case TokenType::Star:       return "Star";
        case TokenType::Slash:      return "Slash";
        case TokenType::Equals:     return "Equals";
        case TokenType::LeftP:     return "LParen";
        case TokenType::RightP:     return "RParen";
        case TokenType::Print:      return "Print";
        case TokenType::End:        return "End";
        default:                    return "Unknown";
    }
}



