#include <parser/parser.h>

using namespace pi::parser;

std::shared_ptr<Block> Parser::parse_block() {
    std::shared_ptr<Block> s(new Block());
    s->m_token = m_curr;
    next_token();
    while (!curr_token_is(Token::TOKEN_RBRACE))
    {
        auto stmt = parse_statement();
        if (stmt)
        {
            s->m_statements.push_back(stmt);
        }
        next_token();
    }
    return s;
}