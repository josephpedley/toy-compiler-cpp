#include "runtime/executor.h"
#include <iostream>
#include <stdexcept>

Executor::Executor(Environment& e)
    : env(e) {}


// Expression evaluation - traversing the tree
int Executor::eval_expr(const Expr* expr) {
    // Number literal
    if (auto n = dynamic_cast<const NumberExpr*>(expr)) {
        return n->value;
    }

    // Variable reference
    if (auto v = dynamic_cast<const VariableExpr*>(expr)) {
        return env.get(v->name);
    }

    // Binary expression
    if (auto b = dynamic_cast<const BinaryExpr*>(expr)) {
        int left  = eval_expr(b->left.get());
        int right = eval_expr(b->right.get());

        switch (b->op) {
            case '+': return left + right;
            case '-': return left - right;
            case '*': return left * right;
            case '/': return left / right;
        }
    }

    throw std::runtime_error("Unknown expression");
}
// Statement execution

void Executor::execute(const Stmt* stmt) {
    // Assignment
    if (auto a = dynamic_cast<const AssignmentStmt*>(stmt)) {
        int value = eval_expr(a->value.get());
        env.set(a->name, value);
        return;
    }

    // Print
    if (auto p = dynamic_cast<const PrintStmt*>(stmt)) {
        int value = eval_expr(p->value.get());
        std::cout << value << "\n";
        return;
    }

    throw std::runtime_error("Unknown statement");
}
