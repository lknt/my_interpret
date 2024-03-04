#include <parser/parser.h>

using namespace pi::parser;

/*写parse_integer函数*/

std::shared_ptr<Expression> Parser::parse_null() {
    std::shared_ptr<Null> e(new Null());
    e->m_token = m_curr;
    while (peek_token_is(Token::TOKEN_SEMICOLON))
    {
        next_token();
    }
    return e;
}