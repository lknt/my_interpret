#include <parser/parser.h>
using namespace pi::parser;

std::shared_ptr<Expression> Parser::parse_ternary(const std::shared_ptr<Expression> &left)
{
    std::shared_ptr<Ternary> e(new Ternary());
    e->m_token = m_curr;
    e->m_condition = left;
    next_token();//跳过问号
    int precedence = curr_token_precedence();
    e->m_if_true = parse_expression(precedence);
    if (!expect_peek_token(Token::TOKEN_COLON))
    {
        return nullptr;
    }
    next_token(); //跳过:
    precedence = curr_token_precedence();
    e->m_if_false = parse_expression(precedence);

    return e;
}