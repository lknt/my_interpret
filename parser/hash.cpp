#include <parser/parser.h>

using namespace pi::parser;


std::shared_ptr<Expression> Parser::parse_hash() {
    std::shared_ptr<Hash> e(new Hash());
    e->m_token = m_curr;
    while (!peek_token_is(Token::TOKEN_RBRACE))
    {
        next_token();
        auto key = parse_expression(LOWEST);
        if (!expect_peek_token(Token::TOKEN_COLON))
        {
            return nullptr;
        }
        next_token();
        auto value = parse_expression(LOWEST);
        e->m_pairs[key] = value;
        if (!peek_token_is(Token::TOKEN_RBRACE) && !expect_peek_token(Token::TOKEN_COMMA))
        {
            return nullptr;
        }

    }
    if (!expect_peek_token(Token::TOKEN_RBRACE))
    {
        return nullptr;
    }
    return e;
}

