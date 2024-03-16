#include <parser/parser.h>

using namespace pi::parser;


/*
 * 应该是遇到了一个operator，传入中缀表达式的左部，完成解析右部expression，返回一个中缀表达式
 * */
std::shared_ptr<Expression> Parser::parse_assign(const std::shared_ptr<Expression> & left) {
    switch (left->type()) {
        case Node::NODE_IDENTIFIER:
        case Node::NODE_INDEX:
        case Node::NODE_PROPERTY:
        {
            std::shared_ptr<Assign> e(new Assign());
            e->m_token = m_curr;
            e->m_name = left;
            int precedence = curr_token_precedence();
            next_token();
            e->m_value = parse_expression(precedence);
            return e;
        }
        default:
        {
            break;
        }
    }
}
