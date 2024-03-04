#include <iostream>

#include <lexer/lexer.h>
using namespace pi::lexer;

#include <parser/parser.h>
using namespace pi::parser;

#include <evaluator/evaluator.h>
using namespace pi::evaluator;

int main()
{
    std::shared_ptr<Environment> env(new Environment());
    std::shared_ptr<Lexer> lexer(new Lexer("./../code.pi"));
    std::shared_ptr<Parser> parser(new Parser(lexer));
    auto program = parser->parse_program();
    auto errors = parser->errors();
    if (!errors.empty())
    {
        for (auto &error : errors)
        {
            std::cout << error << std::endl;
        }
        return -1;
    }

    std::shared_ptr<Evaluator> evaluator(new Evaluator());
    auto evaluated = evaluator->eval(program, env.get());
    if (evaluated)
    {
        if (evaluated->type() != Object::OBJECT_NULL)
            std::cout << evaluated->str() << std::endl;
    }


    return 0;
}