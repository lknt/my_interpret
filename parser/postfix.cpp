#include <parser/parser.h>
using namespace pi::parser;

std::shared_ptr<Expression> Parser::parse_postfix(const std::shared_ptr<Expression> &left) {
    std::shared_ptr<Postfix> e(new Postfix());
    e->m_token = m_curr;
    e->m_operator = m_curr.literal();
    e->m_left = left;
    return e;
}