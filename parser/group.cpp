#include <parser/parser.h>

using namespace pi::parser;

/*
 * 遇到了左括号，解析括号表达式
 * */
std::shared_ptr<Expression> Parser::parse_group()
{
    next_token();//m_curr现在是左括号右边的第一个token
    auto e = parse_expression(LOWEST);
    if (!expect_peek_token(Token::TOKEN_RPAREN))
    {
        return nullptr;
    }
    return e;
}

