#include <parser/parser.h>

using namespace pi::parser;


/*
 * 应该是遇到了一个operator，传入中缀表达式的左部，完成解析右部expression，返回一个中缀表达式
 * */
std::shared_ptr<Expression> Parser::parse_if()
{
    std::shared_ptr<If> e(new If());
    e->m_token = m_curr;
    next_token();

    std::shared_ptr<Scenario> s(new Scenario());
    s->m_condition = parse_expression(LOWEST);
    if (!expect_peek_token(Token::TOKEN_LBRACE))
    {
        return nullptr;
    }
    s->m_body = parse_block();
    e->m_scenarios.push_back(s);
    while (peek_token_is(Token::TOKEN_ELSE))
    {
        next_token();  //到else
        next_token();  //到if
        std::shared_ptr<Scenario> _s(new Scenario());
        if (curr_token_is(Token::TOKEN_IF))
        {
            next_token(); //跳过if
            _s->m_condition = parse_expression(LOWEST);
            if (!expect_peek_token(Token::TOKEN_LBRACE))
            {
                return nullptr;
            }

        }
        else
        {
            //只有else
            Token token(Token::TOKEN_TRUE, "true");
            std::shared_ptr<Bool> b(new Bool());
            b->m_token = token;
            b->m_value = true;
            _s->m_condition = b;
        }
        _s->m_body = parse_block();
        e->m_scenarios.push_back(_s);


    }
    return e;

}