#include <parser/parser.h>

using namespace pi::parser;

/*写parse_integer函数*/

std::shared_ptr<Expression> Parser::parse_list() {
    std::shared_ptr<List> e(new List());
    e->m_token = m_curr;
    e->m_elements = parse_expression_list(Token::TOKEN_RBRACKET);

    return e;
}