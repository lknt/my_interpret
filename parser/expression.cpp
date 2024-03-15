#include <parser/parser.h>

using namespace pi::parser;

/*
 * 解析一个表达式，
 * 先看目前token的类型，去寻找对应的处理方法，如果是整数就看后面的运算符，去解析中缀表达式的右边
 * 如果是左括号，就调用parse_group，也会继续递归调用parse_expression
 * */
std::shared_ptr<Expression> Parser::parse_expression(int precedence) {
    auto prefix = m_prefix_parser_fns.find(m_curr.type());
    //如果没找到，那就是左括号后面token的类型我们还未定义处理方法
    if (prefix == m_prefix_parser_fns.end())
    {
        no_prefix_parse_fn_error(m_curr.type());
        return nullptr;
    }

    //比如是一个整数，那就使用parse_integer，也即prefix->second就是parse_integer的地址
    // 那么谁来使用parse_integer呢，显然是Parse对象，所以使用(this->*(prefix->seccond))()
    std::shared_ptr<Expression> e = (this->*(prefix->second))();
    /*如果m_peek不是分号，并且当前优先级比m_peek的token要小，那么久执行中缀表达式的流程*/
    while (!peek_token_is(Token::TOKEN_SEMICOLON) && precedence < peek_token_precedence())
    {
        auto infix = m_infix_parser_fns.find(m_peek.type());
        /*如果找不到，说明不是运算符*/
        if (infix == m_infix_parser_fns.end())
        {
            return e;
        }
        //m_curr变成operator
        next_token();
        /*需要传入中缀表达式的左部*/
        e = (this->*(infix->second))(e);
    }
    auto postfix = m_postfix_parser_fns.find(m_peek.type());
    if (postfix == m_postfix_parser_fns.end())
    {
        return e;
    }
    next_token();
    e = (this->*(postfix->second))(e);
    return e;
}
//(1+2)*3


std::vector<std::shared_ptr<Expression>> Parser::parse_expression_list(Token::Type end) {
    std::vector<std::shared_ptr<Expression>> expr_list;
    if (peek_token_is(end))
    {
        next_token();
        return expr_list;
    }
    next_token();
    expr_list.push_back(parse_expression(LOWEST));
    while(peek_token_is(Token::TOKEN_COMMA))
    {
        next_token();
        next_token();
        expr_list.push_back(parse_expression(LOWEST));
    }
    if (!expect_peek_token(end))
    {
        return std::vector<std::shared_ptr<Expression>>();
    }
    return expr_list;
}