#include "parser/parser.h"
#include <stdexcept>
#include <cstdlib>

// Constructor
Parser::Parser(const std::vector<Token>& t)
    : tokens(t) {}


// Helper functions
const Token& Parser::peek() const {
    return tokens[pos];
}

const Token& Parser::advance() {
    return tokens[pos++];
}

bool Parser::match(TokenType type) {
    if (peek().type == type) {
        advance();
        return true;
    }
    return false;
}

// statement
std::unique_ptr<Stmt> Parser::parse_statement() {
    if (match(TokenType::Print)) {
        auto expr = parse_expr();
        return std::make_unique<PrintStmt>(std::move(expr));
    }

    if (peek().type == TokenType::Identifier) {
        std::string name = advance().lexeme;

        if (!match(TokenType::Equals)) {
            throw std::runtime_error("Expected '=' after identifier");
        }

        auto value = parse_expr();
        return std::make_unique<AssignmentStmt>(
            std::move(name),
            std::move(value)
        );
    }

    throw std::runtime_error("Expected statement");
}


// expr
std::unique_ptr<Expr> Parser::parse_expr() {
    auto left = parse_term();

    while (peek().type == TokenType::Plus ||
           peek().type == TokenType::Minus) {
        char op = advance().lexeme[0];
        auto right = parse_term();

        left = std::make_unique<BinaryExpr>(
            op,
            std::move(left),
            std::move(right)
        );
    }

    return left;
}

// term (* and /)
std::unique_ptr<Expr> Parser::parse_term() {
    auto left = parse_factor();

    while (peek().type == TokenType::Star ||
           peek().type == TokenType::Slash) {
        char op = advance().lexeme[0];
        auto right = parse_factor();

        left = std::make_unique<BinaryExpr>(
            op,
            std::move(left),
            std::move(right)
        );
    }

    return left;
}


// factor (number and =)
std::unique_ptr<Expr> Parser::parse_factor() {
    if (match(TokenType::Number)) {
        int value = std::stoi(tokens[pos - 1].lexeme);
        return std::make_unique<NumberExpr>(value);
    }

    if (match(TokenType::Identifier)) {
        return std::make_unique<VariableExpr>(
            tokens[pos - 1].lexeme
        );
    }

    if (match(TokenType::LeftP)) {
        auto expr = parse_expr();
        
        if (!match(TokenType::RightP)) {
            throw std::runtime_error("Expected ')'");
        }

        return expr;
    }

    throw std::runtime_error("Expected expression");
}
