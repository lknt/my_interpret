
#include <lexer/lexer.h>

#include <ast/header.h>
using namespace pi::lexer;
using namespace pi::token;
using namespace pi::ast;

class A{
public:
    int a;
    std::ostream & operator<< (std::ostream &out)
    {
        out << a ;
        return out;
    }
};
int main()
{

    /*测试Integer.h*/
//    Integer Int;
//    Int.m_values = 6;
//
//    Json tokens;
//    tokens.append(Int.json());
//    Json json;
//    json["tokens"] = tokens;
//    std::ofstream ofs("./../token.json");
//    ofs << json.str();
//    ofs.close();

    /*测试infix.h*/
//    Infix infix;
//    Integer Int1(7), Int2(8);
//    infix.m_operator = "+";
//    infix.m_left = std::make_shared<Integer>(Int1);
//    infix.m_right = std::make_shared<Integer>(Int2);
//
//    Json tokens;
//    tokens.append(infix.json());
//    Json json;
//    json["tokens"] = tokens;
//    std::ofstream ofs("./../token.json");
//    ofs << json.str();
//    ofs.close();


    /*测试expression_statement.h*/
//    Expression_Statement exp;
//    Integer Int1(7), Int2(8);
//    exp.m_expression = std::make_shared<Integer>(Int1);
//
//    Json tokens;
//    tokens.append(exp.json());
//    Json json;
//    json["tokens"] = tokens;
//    std::ofstream ofs("./../token.json");
//    ofs << json.str();
//    ofs.close();

//    Program program;
//    Integer Int1(7), Int2(8);
//
//    Infix infix;
//    infix.m_operator = "+";
//    infix.m_left = std::make_shared<Integer>(Int1);
//    infix.m_right = std::make_shared<Integer>(Int2);
//
//
//    Expression_Statement exp1;
//    exp1.m_expression = std::make_shared<Integer>(Int1);
//
//    Expression_Statement exp2;
//    exp2.m_expression = std::make_shared<Infix>(infix);
//
//
//    program.m_statement.push_back(std::make_shared<Expression_Statement>(exp1));
//
//    program.m_statement.push_back(std::make_shared<Expression_Statement>(exp2));
//
//    Json tokens;
//    tokens.append(program.json());
//    Json json;
//    json["tokens"] = tokens;
//    std::ofstream ofs("./../token.json");
//    ofs << json.str();
//    ofs.close();

    /*测试lexer*/
    auto lexer = new Lexer("./../code.pi");
    Json tokens;
    while (true)
    {
        auto token = lexer->next_token();
        std::cout << token.show() << std::endl;
        tokens.append(token.json());
        if (token.type() == Token::TOKEN_EOF)
        {
            break;
        }
    }
    Json json;
    json["tokens"] = tokens;

    std::ofstream ofs("./../token.json");
    ofs << json.str();
    ofs.close();


    /* 测试token*/
//    Token tk(Token::TOKEN_INTEGER, "66");
//    std::cout << tk;



    return 0;
}