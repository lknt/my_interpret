#include <parser/parser.h>

using namespace pi::parser;

/*写parse_integer函数*/

std::shared_ptr<Expression> Parser::parse_float()
{
    std::shared_ptr<Float> e(new Float());
    e->m_token = m_curr;
    e->m_values = std::stod(m_curr.literal());
    return e;
}