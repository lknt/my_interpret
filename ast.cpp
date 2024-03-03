#include <parser/parser.h>

using namespace pi::parser;

int main()
{

    std::shared_ptr<Lexer> lexer (new Lexer("./../code.pi"));

    std::shared_ptr<Parser> parser (new Parser(lexer));
    std::shared_ptr<Program> program = parser->parse_program();
    /*
     * Node->Expression
     * Node->Statement->Expression_Statement
     * Node->Statement->Program
     * Expression_Statement里面有一个Expression指针
     * Program里面有一链表的Statement
     * */
    Json json = program->json();

    std::ofstream ofs("./../ast.json");
    ofs << json.str();
    ofs.close();


    return 0;
}