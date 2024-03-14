#include <parser/parser.h>

using namespace pi::parser;


/*
 * 应该是遇到了一个operator，传入中缀表达式的左部，完成解析右部expression，返回一个中缀表达式
 * */
std::shared_ptr<Expression> Parser::parse_while() {
    std::shared_ptr<While> e(new While());
    e->m_token = m_curr;
    next_token();
    e->m_condition = parse_expression(LOWEST);
    if (!expect_peek_token(Token::TOKEN_LBRACE))
    {
        return nullptr;
    }
    e->m_body = parse_block();
    return e;
}
