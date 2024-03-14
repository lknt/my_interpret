#include <parser/parser.h>

using namespace pi::parser;

std::shared_ptr<Break> Parser::parse_break() {
    std::shared_ptr<Break> s(new Break());
    s->m_token = m_curr;
    while (curr_token_is(Token::TOKEN_COLON))
    {
        next_token();
    }
    return s;
}