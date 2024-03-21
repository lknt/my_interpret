#include <parser/parser.h>

using namespace pi::parser;


std::shared_ptr<Expression> Parser::parse_dot(const std::shared_ptr<Expression> &left)
{
    Token token = m_curr;
    next_token();
    if (peek_token_is(Token::TOKEN_LPAREN))
    {
        //method obj.method()
        std::shared_ptr<Method> e(new Method());
        e->m_token = token;
        e->m_object = left;
        e->m_method = parse_identifier();
        next_token();
        e->m_arguments = parse_expression_list(Token::TOKEN_RPAREN);
        return e;
    }
    else
    {
        //property  obj.property
        std::shared_ptr<Property> e(new Property());
        e->m_token = m_curr;
        e->m_object = left;
        e->m_property = parse_identifier();
        return e;
    }
}