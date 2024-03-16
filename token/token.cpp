//
// Created by 19484 on 2024-02-24.
//

#include <token/token.h>



using namespace pi::token;


std::map<Token::Type, string> Token::m_name = {
        {TOKEN_ILLEGAL, "illegal"},
        {TOKEN_INTEGER, "integer"},
        {TOKEN_FLOAT, "float"},
        {TOKEN_STRING, "string"},
        {TOKEN_EOF, "eof"},
        {TOKEN_PLUS, "+"},
        {TOKEN_MINUS, "-"},
        {TOKEN_ASTERISK, "*"},
        {TOKEN_SLASH, "/"},
        {TOKEN_MODULO, "%"},
        {TOKEN_TILDE, "~"},
        {TOKEN_BIT_AND, "&"},
        {TOKEN_BIT_OR, "|"},
        {TOKEN_BIT_XOR, "^"},
        {TOKEN_BIT_LSHIFT, "<<"},
        {TOKEN_BIT_RSHIFT, ">>"},
        {TOKEN_LT, "<"},
        {TOKEN_GT, ">"},
        {TOKEN_LE, "<="},
        {TOKEN_GE, ">="},
        {TOKEN_NE, "!="},
        {TOKEN_EQ, "=="},
        {TOKEN_AND, "&&"},
        {TOKEN_OR, "||"},
        {TOKEN_NOT, "!"},

        {TOKEN_LPAREN, "("},
        {TOKEN_RPAREN, ")"},
        {TOKEN_SEMICOLON, ";"},

        {TOKEN_IDENTIFIER, "identifier"},
        {TOKEN_TRUE, "true"},
        {TOKEN_FALSE, "false"},
        {TOKEN_NULL, "null"},
        {TOKEN_ASSIGN, "="},

        {TOKEN_PLUS_ASSIGN, "+="},
        {TOKEN_MINUS_ASSIGN, "-="},
        {TOKEN_ASTERISK_ASSIGN,"*="},
        {TOKEN_SLASH_ASSIGN,"/="},
        {TOKEN_MODULO_ASSIGN,"%="},
        {TOKEN_BIT_OR_ASSIGN,"|="},
        {TOKEN_BIT_AND_ASSIGN,"&="},
        {TOKEN_BIT_XOR_ASSIGN,"^="},
        {TOKEN_BIT_LSHIFT_ASSIGN,"<<="},
        {TOKEN_BIT_RSHIFT_ASSIGN,">>="},
        {TOKEN_INCREASE,"++"},
        {TOKEN_DECREASE,"--"},

        {TOKEN_QUESTION, "?"},
        {TOKEN_COLON, ":"},
        {TOKEN_IF, "if"},
        {TOKEN_ELSE, "else"},
        {TOKEN_LBRACE, "{"},
        {TOKEN_RBRACE, "}"},

        {TOKEN_CONTINUE, "continue"},
        {TOKEN_BREAK, "break"},
        {TOKEN_WHILE, "while"},

        {TOKEN_FOR, "for"},

        {TOKEN_SWITCH, "switch"},
        {TOKEN_CASE, "case"},
        {TOKEN_DEFAULT, "default"},
        {TOKEN_COMMA, ","},

        {TOKEN_LBRACKET, "["},
        {TOKEN_RBRACKET, "]"},

        {TOKEN_DOT, "."},

        {TOKEN_IN, "in"},

        {TOKEN_FUNCTION, "function"},
        {TOKEN_RETURN, "return"},
};

std::map<string, Token::Type> Token::m_keywords = {
        {"true", TOKEN_TRUE},
        {"false", TOKEN_FALSE},
        {"null", TOKEN_NULL},
        {"if", TOKEN_IF},
        {"else", TOKEN_ELSE},
        {"while", TOKEN_WHILE},
        {"continue", TOKEN_CONTINUE},
        {"break", TOKEN_BREAK},
        {"for", TOKEN_FOR},
        {"switch", TOKEN_SWITCH},
        {"case", TOKEN_CASE},
        {"default", TOKEN_DEFAULT},
        {"in", TOKEN_IN},
        {"fn", TOKEN_FUNCTION},
        {"return", TOKEN_RETURN},

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

