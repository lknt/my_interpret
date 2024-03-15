#include <parser/parser.h>

using namespace pi::parser;


std::shared_ptr<Expression> Parser::parse_index(const std::shared_ptr<Expression> &left) {
    std::shared_ptr<Index> e(new Index());
    e->m_token = m_curr;
    e->m_left = left;
    next_token();
    e->m_index = parse_expression(LOWEST);
    if (!expect_peek_token(Token::TOKEN_RBRACKET))
    {
        return nullptr;
    }
    return e;
}

