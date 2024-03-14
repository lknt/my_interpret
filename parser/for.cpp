#include <parser/parser.h>

using namespace pi::parser;

/*写parse_integer函数*/

std::shared_ptr<Expression> Parser::parse_for() {
    std::shared_ptr<For> e(new For());
    e->m_token = m_curr;
    next_token();
    e->m_starter = parse_expression(LOWEST);
    if (!e->m_starter)
    {
        return nullptr;
    }
    next_token();
    while (curr_token_is(Token::TOKEN_SEMICOLON))
    {
        next_token();
    }
    e->m_condition = parse_expression(LOWEST);
    if (!e->m_condition)
    {
        return nullptr;
    }
    next_token();
    while (curr_token_is(Token::TOKEN_SEMICOLON))
    {
        next_token();
    }
    e->m_closer = parse_expression(LOWEST);
    if (!e->m_closer)
    {
        return nullptr;
    }
    next_token();
    if (!curr_token_is(Token::TOKEN_LBRACE))
    {
        return nullptr;
    }
    e->m_body = parse_block();
    return e;

}