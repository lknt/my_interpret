#include <parser/parser.h>

using namespace pi::parser;


/*解析语句，直接返回parse_expression_statement
 * Statement是继承于node的
 * */
std::shared_ptr<Statement> Parser::parse_statement()
{
    return parse_expression_statement();
}

/* 返回一个表达式语句，（就是包含了一个表达式指针的类
 * Expression_Statement继承于Statement
 * */
std::shared_ptr<Expression_Statement> Parser::parse_expression_statement()
{
    std::shared_ptr<Expression_Statement> s(new Expression_Statement());
    s->m_token = m_curr;
    s->m_expression = parse_expression(LOWEST);
    while (peek_token_is(Token::TOKEN_SEMICOLON))
    {
        next_token();
    }
    return s;
}