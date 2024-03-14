#include <parser/parser.h>

using namespace pi::parser;

std::shared_ptr<Continue> Parser::parse_continue() {
    std::shared_ptr<Continue> s(new Continue());
    s->m_token = m_curr;
    while (curr_token_is(Token::TOKEN_COLON))
    {
        next_token();
    }
    return s;
}