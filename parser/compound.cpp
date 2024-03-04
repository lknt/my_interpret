#include <parser/parser.h>

using namespace pi::parser;


/*
 * 应该是遇到了一个operator，传入中缀表达式的左部，完成解析右部expression，返回一个中缀表达式
 * */
std::shared_ptr<Expression> Parser::parse_compound(const std::shared_ptr<Expression> &left) {
        std::shared_ptr<Compound> e(new Compound());
        e->m_token = m_curr;
        e->m_operator = m_curr.literal();
        e->m_left = left;
        int precedence = curr_token_precedence();
        next_token();
        e->m_right = parse_expression(precedence);
        return e;
}
