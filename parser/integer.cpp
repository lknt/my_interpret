#include <parser/parser.h>

using namespace pi::parser;

/*写parse_integer函数*/

std::shared_ptr<Expression> Parser::parse_integer()
{
    std::shared_ptr<Integer> e(new Integer());
    e->m_token = m_curr;
    e->m_values = std::stol(m_curr.literal());
    return e;
}