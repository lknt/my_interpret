#include <parser/parser.h>

using namespace pi::parser;


std::shared_ptr<Return> Parser::parse_return() {
    std::shared_ptr<Return> s(new Return());
    s->m_token = m_curr;
    next_token();
    s->m_value = parse_expression(LOWEST);
    while (curr_token_is(Token::TOKEN_SEMICOLON))
    {
        next_token();
    }
    return s;
}
