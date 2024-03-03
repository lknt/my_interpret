#include <parser/parser.h>

using namespace pi::parser;


std::shared_ptr<Program> Parser::parse_program()
{
    std::shared_ptr<Program> s(new Program());

    while (m_curr.type() != Token::TOKEN_EOF)
    {
        /*parse_statement会转到parse_expression_statement去解析表达式
         * 会去parse_expression，去检索前缀map里面的操作方法*/
        auto stmt = parse_statement();

        /*如果解析到一条语句*/
        if (stmt)
        {
            s->m_statement.push_back(stmt);
        }
        next_token();
    }
    return s;
}