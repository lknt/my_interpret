#include <parser/parser.h>

using namespace pi::parser;

std::shared_ptr<Expression> Parser::parse_call(const std::shared_ptr<Expression> &left) {
    std::shared_ptr<Call> e(new Call());
    e->m_token = m_curr;
    e->m_function = left;
    e->m_arguments = parse_expression_list(Token::TOKEN_RPAREN);
    return e;
}