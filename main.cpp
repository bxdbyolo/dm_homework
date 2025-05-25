
#include <iostream>
#include "lib/lexer.h"
#include "lib/grammar.h"
#include "lib/parser.h"

void test(const std::string& input, bool should_pass = true) {
    static Grammar grammar;

    try {
        Lexer lexer(input);
        auto tokens = lexer.tokenize();

        Parser parser(grammar, std::move(tokens));
        const auto ast = parser.parse();

        std::cout << "[PASS] " << input << std::endl;
        ast->print(1);

        if (!should_pass)
            std::cout << "[FAIL] Expected failure but passed: " << input << std::endl;

    } catch (const std::exception& e) {
        if (should_pass)
            std::cout << "[FAIL] " << input << " - " << e.what() << std::endl;
        else
            std::cout << "[PASS] (expected failure) " << input << " - " << e.what() << std::endl;
    }
}

int main() {
    test("a");
    test("a|b");
    test("a*");
    test("a+");
    test("a?");
    test("(a)");
    test("ab");
    test("a(b|c)*");

    test("", false);
    test("A", false);
    test("1", false);
    test("a||b", false);
    test("*a", false);
    test("a)", false);

}
