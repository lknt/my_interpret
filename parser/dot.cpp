#include <parser/parser.h>

using namespace pi::parser;


std::shared_ptr<Expression> Parser::parse_dot(const std::shared_ptr<Expression> &left)
{
    std::shared_ptr<Property> e(new Property());
    e->m_token = m_curr;
    e->m_object = left;

    next_token();
    e->m_property = parse_identifier();
    return e;
}