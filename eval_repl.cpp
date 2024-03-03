#include <iostream>

#include <lexer/lexer.h>
using namespace pi::lexer;

#include <parser/parser.h>
using namespace pi::parser;

#include <evaluator/evaluator.h>
using namespace pi::evaluator;



const string prompt = "<<";

int main()
{
    std::cout << "Welcome to pi programming language!" << std::endl;


    std::shared_ptr<Evaluator> evaluator(new Evaluator());

    while (true)
    {
        std::cout << prompt;
        string text;
        std::getline(std::cin, text);

        std::shared_ptr<Lexer> lexer(new Lexer(text.c_str(), text.size()));
        std::shared_ptr<Parser> parser(new Parser(lexer));
        auto program = parser->parse_program();
        auto errors = parser->errors();
        if (!errors.empty())
        {
            for (auto &error : errors)
            {
                std::cout << "parser_error:" << error << std::endl;
            }
            continue;
        }


        auto evaluated = evaluator->eval(program);
        if (evaluated)
        {
            std::cout << "eval: " << evaluated->str() << std::endl;
        }
    }



    return 0;
}