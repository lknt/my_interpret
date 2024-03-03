//
// Created by 19484 on 2024-02-24.
//

#include <token/token.h>



using namespace pi::token;


std::map<Token::Type, string> Token::m_name = {
        {Token::TOKEN_ILLEGAL, "illegal"},
        {Token::TOKEN_INTEGER, "integer"},
        {Token::TOKEN_FLOAT, "float"},
        {Token::TOKEN_EOF, "eof"},
        {Token::TOKEN_PLUS, "+"},
        {Token::TOKEN_MINUS, "-"},
        {Token::TOKEN_ASTERISK, "*"},
        {Token::TOKEN_SLASH, "/"},
        {Token::TOKEN_MODULO, "%"},
        {Token::TOKEN_TILDE, "~"},
        {Token::TOKEN_BIT_AND, "&"},
        {Token::TOKEN_BIT_OR, "|"},
        {Token::TOKEN_BIT_XOR, "^"},
        {Token::TOKEN_BIT_LSHIFT, "<<"},
        {Token::TOKEN_BIT_RSHIFT, ">>"},
        {Token::TOKEN_LT, "<"},
        {Token::TOKEN_GT, ">"},
        {Token::TOKEN_LE, "<="},
        {Token::TOKEN_GE, ">="},
        {Token::TOKEN_NE, "!="},
        {Token::TOKEN_EQ, "=="},
        {Token::TOKEN_AND, "&&"},
        {Token::TOKEN_OR, "||"},
        {Token::TOKEN_NOT, "!"},

        {Token::TOKEN_LPAREN, "("},
        {Token::TOKEN_RPAREN, ")"},
        {Token::TOKEN_SEMICOLON, ";"},
        {Token::TOKEN_TRUE, "true"},
        {Token::TOKEN_FALSE, "false"},
};

std::map<string, Token::Type> Token::m_keywords = {
        {"true", TOKEN_TRUE},
        {"false", TOKEN_FALSE},
};

Token::Token() : m_type(TOKEN_ILLEGAL){

}

Token::Token(pi::token::Token::Type type, const std::string& literal) : m_type(type), m_literal(literal){
}

Token::Type Token::type() const
{
    return m_type;
}

string Token::name() const
{
    auto it = m_name.find(m_type);
    if (it != m_name.end())
    {
        return it->second;
    }
    return "";
}
string Token::literal() const
{
    return m_literal;
}

string Token::show() const
{
    string res = "token " + literal() + " is " + name();
    return res;
}
Json Token::json() const
{
    Json json;
    json["type"] = type();
    json["name"] = m_literal;
    return json;
}

Token& Token::operator=(const Token &other)
{
    if (this == &other)
    {
        return *this;
    }
    m_type = other.m_type;
    m_literal = other.m_literal;
    return *this;
}

Token::Type Token::lookup(const string & identifier)
{
    auto it = m_keywords.find(identifier);
    if (it != m_keywords.end())
    {
        return it->second;
    }
    return TOKEN_IDENTIFIER;
}

