#include <parser/parser.h>

using namespace pi::parser;

/*写parse_integer函数*/

std::shared_ptr<Expression> Parser::parse_foreach(const pi::token::Token & token) {
    std::shared_ptr<Foreach> e(new Foreach());
    e->m_token = token;
    if (!curr_token_is(Token::TOKEN_IDENTIFIER))
    {
        return nullptr;
    }
    string key;
    string val = m_curr.literal();
    next_token();
    if (curr_token_is(Token::TOKEN_COMMA))
    {
        next_token();
        if (!curr_token_is(Token::TOKEN_IDENTIFIER))
        {
            return nullptr;
        }
        key = val;
        val = m_curr.literal();
        next_token();
    }
    e->m_key = key;
    e->m_value = val;
    if (!curr_token_is(Token::TOKEN_IN))
    {
        return nullptr;
    }
    next_token();
    e->m_iterable = parse_expression(LOWEST);
    if (!expect_peek_token(Token::TOKEN_LBRACE))
    {
        return nullptr;
    }
    e->m_body = parse_block();
    return e;

}