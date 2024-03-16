#include <parser/parser.h>

using namespace pi::parser;


std::shared_ptr<Expression> Parser::parse_in(const std::shared_ptr<Expression> &left) {
    std::shared_ptr<In> e(new In());
    e->m_token = m_curr;
    e->m_left = left;
    int precedence = curr_token_precedence();
    next_token();
    e->m_right = parse_expression(precedence);
    return e;
}

