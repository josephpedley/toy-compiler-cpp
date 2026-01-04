#pragma once
#include "parser/ast.h"
#include "runtime/environment.h"

class Executor {
public:
    explicit Executor(Environment& env);

    void execute(const Stmt* stmt);

private:
    int eval_expr(const Expr* expr);

private:
    Environment& env;
};
