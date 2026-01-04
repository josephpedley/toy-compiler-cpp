// Recursive descent parser

#pragma once
#include <vector>
#include <memory>
#include "lexer/token.h"
#include "parser/ast.h"



class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens);

    // Parse a single statement
    std::unique_ptr<Stmt> parse_statement();
    bool is_at_end() const;


private:
    // Expression parsing 
    std::unique_ptr<Expr> parse_expr();
    std::unique_ptr<Expr> parse_term();
    std::unique_ptr<Expr> parse_factor();

    // Token helpers
    const Token& peek() const;
    const Token& advance();
    bool match(TokenType type);

private:
    const std::vector<Token>& tokens;
    size_t pos = 0;
};
