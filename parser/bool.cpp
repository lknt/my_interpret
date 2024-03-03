#include <parser/parser.h>

using namespace pi::parser;

std::shared_ptr<Expression> Parser::parse_bool() {
    std::shared_ptr<Bool> e(new Bool());
    e->m_token = m_curr;
    e->m_value = curr_token_is(Token::TOKEN_TRUE);
    return e;
}