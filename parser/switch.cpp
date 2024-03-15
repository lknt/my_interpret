#include <parser/parser.h>
using namespace pi::parser;

std::shared_ptr<Expression> Parser::parse_switch() {
    std::shared_ptr<Switch> e(new Switch());
    e->m_token = m_curr;
    next_token();
    e->m_value = parse_expression(LOWEST);
    if (!e->m_value)
    {
        return nullptr;
    }
    if (!expect_peek_token(Token::TOKEN_LBRACE))
    {
        return nullptr;
    }
    next_token();
    while (!curr_token_is(Token::TOKEN_RBRACE))
    {
        std::shared_ptr<Case> c(new Case());
        if (curr_token_is(Token::TOKEN_DEFAULT))
        {
            c->m_default = true;
        }
        else if (curr_token_is(Token::TOKEN_CASE))
        {
            next_token();
            c->m_values.push_back(parse_expression(LOWEST));
            while (peek_token_is(Token::TOKEN_COMMA))
            {
                next_token();
                next_token();
                c->m_values.push_back(parse_expression(LOWEST));
            }
        }
        else
        {
            std::ostringstream oss;
            oss << "expected case|default: " << m_curr.type();
            m_errors.push_back(oss.str());
            return nullptr;
        }
        if (!expect_peek_token(Token::TOKEN_COLON))
        {
            return nullptr;
        }

        std::shared_ptr<Block> body(new Block());
        body->m_token = m_curr;
        next_token();
        while(!curr_token_is(Token::TOKEN_CASE) && !curr_token_is(Token::TOKEN_DEFAULT))
        {
            if (curr_token_is(Token::TOKEN_RBRACE))
            {
                break;
            }
            auto stmt = parse_statement();
            body->m_statements.push_back(stmt);
            next_token();
        }
        c->m_body = body;
        e->m_cases.push_back(c);
    }
    if (!curr_token_is(Token::TOKEN_RBRACE))
    {
        return nullptr;
    }
    return e;
}