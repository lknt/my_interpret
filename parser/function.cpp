#include <parser/parser.h>

using namespace pi::parser;

/*写parse_integer函数*/

std::shared_ptr<Expression> Parser::parse_function() {
    std::shared_ptr<Function> e(new Function());
    e->m_token = m_curr;
    if (!expect_peek_token(Token::TOKEN_LPAREN))
    {
        return nullptr;
    }
    if (!parse_function_parameters(e))
    {
        return nullptr;
    }
    if (!expect_peek_token(Token::TOKEN_LBRACE))
    {
        return nullptr;
    }

    e->m_body = parse_block();

    return e;
}

bool Parser::parse_function_parameters(const std::shared_ptr<Function> &fn) {
    while (!peek_token_is(Token::TOKEN_RPAREN))
    {
        next_token();
        if (curr_token_is(Token::TOKEN_COMMA))
        {
            continue;
        }
        std::shared_ptr<Identifier> ident(new Identifier());
        ident->m_token = m_curr;
        ident->m_value = m_curr.literal();
        fn->m_parameters.push_back(ident);
    }
    if (!expect_peek_token(Token::TOKEN_RPAREN))
    {
        return false;
    }
    return true;
}
