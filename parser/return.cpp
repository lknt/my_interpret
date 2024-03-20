#include <parser/parser.h>

using namespace pi::parser;


std::shared_ptr<Return> Parser::parse_return() {
    std::shared_ptr<Return> s(new Return());
    s->m_token = m_curr;
    if (m_curr.line() < m_peek.line())
    {
        std::shared_ptr<Null> e(new Null());
        e->m_token = Token(Token::TOKEN_NULL, "null", m_curr.line(), m_curr.column());
        s->m_value = e;
        return s;
    }

    next_token();
    s->m_value = parse_expression(LOWEST);
    while (curr_token_is(Token::TOKEN_SEMICOLON))
    {
        next_token();
    }
    return s;
}
