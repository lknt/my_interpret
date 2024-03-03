#include <parser/parser.h>
using namespace pi::parser;

std::shared_ptr<Expression> Parser::parse_prefix() {
    std::shared_ptr<Prefix> e(new Prefix());
    e->m_token = m_curr;
    e->m_operator = m_curr.literal();
    next_token();
    e->m_right = parse_expression(PREFIX);
    return e;
}