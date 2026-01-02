#pragma once
#include <memory>
#include <string>

// Base AST node types.
struct Expr{
    virtual ~Expr() = default;
};
struct Stmt{
    virtual ~Stmt() = default;
};

// Expression nodes
struct NumberExpr:Expr{
    int value;

    explicit NumberExpr(int v) : value(v){}
};

struct VariableExpr:Expr{
    std::string name;

    explicit VariableExpr(std::string n) : name(std::move(n)){}
};

struct BinaryExpr:Expr{
    char op;
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;

    BinaryExpr(char o, std::unique_ptr<Expr> l, std::unique_ptr<Expr> r) : op(o), left(std::move(l)), right(std::move(r)){}
};

// Statement nodes
struct AssignmentStmt:Stmt {
    std::string name;
    std::unique_ptr<Expr> value;

    AssignmentStmt(std::string n, std::unique_ptr<Expr> v) : name(std::move(n)), value(std::move(v)){}
};

struct PrintStmt:Stmt{
    std::unique_ptr<Expr> value;

    explicit PrintStmt(std::unique_ptr<Expr> v) : value(std::move(v)){}
};