#include <parser/parser.h>

using namespace pi::parser;

/*
 * 遇到了左括号，解析括号表达式
 * */
std::shared_ptr<Expression> Parser::parse_identifier() {
    std::shared_ptr<Identifier> e(new Identifier());
    e->m_token = m_curr;
    e->m_value = m_curr.literal();
    return e;
}

