//
// Created by 19484 on 2024-02-25.
//

#include <parser/parser.h>
using namespace pi::parser;

std::map<Token::Type, int> Parser::m_precedences = {
        {Token::TOKEN_BIT_AND, LOGIC},
        {Token::TOKEN_BIT_OR, LOGIC},
        {Token::TOKEN_BIT_XOR, LOGIC},
        {Token::TOKEN_BIT_LSHIFT, LOGIC},
        {Token::TOKEN_BIT_RSHIFT, LOGIC},
        {Token::TOKEN_PLUS, SUM},
        {Token::TOKEN_MINUS, SUM},
        {Token::TOKEN_ASTERISK, PRODUCT},
        {Token::TOKEN_SLASH, PRODUCT},
        {Token::TOKEN_MODULO, PRODUCT},

};

std::map<Token::Type, Parser::prefix_parser_fn> Parser::m_prefix_parser_fns = {
        {Token::TOKEN_INTEGER, &Parser::parse_integer},
        {Token::TOKEN_FLOAT, &Parser::parse_float},
        {Token::TOKEN_TRUE, &Parser::parse_bool},
        {Token::TOKEN_FALSE, &Parser::parse_bool},
        {Token::TOKEN_LPAREN, &Parser::parse_group},
        {Token::TOKEN_MINUS, &Parser::parse_prefix},
        {Token::TOKEN_TILDE, &Parser::parse_prefix},

};

std::map<Token::Type, Parser::infix_parser_fn> Parser::m_infix_parser_fns = {
        {Token::TOKEN_PLUS, &Parser::parse_infix},
        {Token::TOKEN_MINUS, &Parser::parse_infix},
        {Token::TOKEN_ASTERISK, &Parser::parse_infix},
        {Token::TOKEN_SLASH, &Parser::parse_infix},
        {Token::TOKEN_MODULO, &Parser::parse_infix},
        {Token::TOKEN_BIT_AND, &Parser::parse_infix},
        {Token::TOKEN_BIT_OR, &Parser::parse_infix},
        {Token::TOKEN_BIT_XOR, &Parser::parse_infix},
        {Token::TOKEN_BIT_LSHIFT, &Parser::parse_infix},
        {Token::TOKEN_BIT_RSHIFT, &Parser::parse_infix},
};

Parser::Parser() {}


/*需要调用两次next_token，用来初始化m_curr和m_peek*/
Parser::Parser(std::shared_ptr<Lexer> &lexer) : m_lexer(lexer)
{
    next_token();
    next_token();
}

Parser::~Parser() {}

void Parser::next_token() {
    m_curr = m_peek;
    m_peek = m_lexer->next_token();
}

bool Parser::curr_token_is(Token::Type type)
{
    return m_curr.type() == type;
}

bool Parser::peek_token_is(Token::Type type)
{
    return m_peek.type() == type;
}

/*如果接收到类型相符的token，就执行一次next_token，不同的话，就报告错误*/
bool Parser::expect_peek_token(Token::Type type) {
    if (peek_token_is(type)) {
        next_token();
        return true;
    }
    else
    {
        peek_error(type);
        return false;
    }
}

void Parser::peek_error(Token::Type type) {
    std::ostringstream oss;
    oss << "expect next token to be " << Token::m_name[type] << ", got " << m_peek.name() << " instead";
    m_errors.push_back(oss.str());
}

/*返回m_curr的优先级*/
int Parser::curr_token_precedence()
{
    auto it = m_precedences.find(m_curr.type());
    if (it != m_precedences.end())
    {
        return it->second;
    }
    return LOWEST;
}

int Parser::peek_token_precedence()
{
    auto it = m_precedences.find(m_peek.type());
    if (it != m_precedences.end())
    {
        return it->second;
    }
    return LOWEST;
}

void Parser::no_prefix_parse_fn_error(Token::Type type)
{
    std::ostringstream oss;
    oss << "no prefix parse function for " << Token::m_name[type] << " " << m_curr.literal();
    m_errors.push_back((oss.str()));
}

std::list<string> & Parser::errors()
{
    return m_errors;
}