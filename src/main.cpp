#include <iostream>
#include <vector>
#include <string>

#include "lexer/lexer.h"
#include "lexer/token.h"
#include "parser/parser.h"
#include "runtime/environment.h"
#include "runtime/executor.h"

int main() {
    // ======================
    // Source program
    // ======================
    std::string source =
        "x = 3 + 4 * (2 - 1)\n"
        "print x";

    std::cout << "===== SOURCE =====\n";
    std::cout << source << "\n\n";

    // ======================
    // LEXER
    // ======================
    std::cout << "===== TOKENS =====\n";

    Lexer lexer(source);
    std::vector<Token> tokens;

    while (true) {
        Token t = lexer.next_token();
        tokens.push_back(t);

        std::cout
            << token_type_to_string(t.type)
            << " : '" << t.lexeme << "'\n";

        if (t.type == TokenType::End)
            break;
    }

    // ======================
    // PARSER + EXECUTION
    // ======================
    std::cout << "\n===== EXECUTION =====\n";

    try {
        Parser parser(tokens);
        Environment env;
        Executor executor(env);

        // Parse + execute until End token
        while (!parser.is_at_end()) {
            auto stmt = parser.parse_statement();
            executor.execute(stmt.get());
            }


    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
