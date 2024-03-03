//
// Created by 19484 on 2024-02-24.
//

#include <lexer/lexer.h>
using namespace pi::lexer;
using namespace pi::token;

Lexer::Lexer() {
    m_ch = 0;
    m_pos = 0;
    m_next_pos = 0;
}



// 打开文件前要看是否打开成功
Lexer::Lexer(const std::string &file) {
    m_ch = 0;
    m_pos = 0;
    m_next_pos = 0;
    std::ifstream ifs(file);
    if (!ifs.good())
    {
        std::cout << "file " << file << " not found" << std::endl;
        return;
    }
    std::ostringstream oss;
    oss << ifs.rdbuf();
    m_input = oss.str();
}

Lexer::Lexer(const char *buf, int len) {
    m_ch = 0;
    m_pos = 0;
    m_next_pos = 0;
    m_input.assign(buf, len);
}


// m_pos m_ch和m_next_pos一开始都为0，其实m_pos应该为-1
// 每次更新m_pos会直接等于m_next_pos
void Lexer::read_char()
{
    if (m_next_pos >= m_input.size())
    {
        m_ch = 0;
    }
    else {
        m_ch = m_input[m_next_pos];
    }
    m_pos = m_next_pos;
    m_next_pos ++;

}

char Lexer::peek_char() {
    if (m_next_pos >= m_input.size())
    {
        return 0;
    }
    else {
        return m_input[m_next_pos];
    }
}

void Lexer::unread_char() {
    m_next_pos = m_pos;
    m_pos = m_pos - 1;
}

void Lexer::skip_white_space()
{
    while (m_ch == ' ' || m_ch == '\t' || m_ch == '\n')
    {
        read_char();
    }
}

bool Lexer::is_digit(char ch) const
{
    return ch <= '9' && ch >= '0';
}

bool Lexer::is_letter(char ch) const
{
    return (ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A') || m_ch == '_';
}

string Lexer::read_number()
{
    int pos = m_pos;
    while(isdigit(m_ch))
    {
        read_char();
    }
    return m_input.substr(pos, m_pos - pos);
}

string Lexer::read_identifier() {
    int pos = m_pos;
    while(is_letter(m_ch) || is_digit(m_ch))
    {
        read_char();
    }
    return m_input.substr(pos, m_pos - pos);
}

Token Lexer::new_token(Token::Type type, const std::string &literal) {
    Token token(type, literal);
    return token;
}

//
Token Lexer::next_token() {
    read_char();
    skip_white_space();
    switch(m_ch)
    {
        case '+':
        {
            string literal = "";
            literal += m_ch;
            return new_token(Token::TOKEN_PLUS, literal);
        }
        case '-':
        {
            string literal = "";
            literal += m_ch;
            return new_token(Token::TOKEN_MINUS, literal);
        }
        case '*':
        {
            string literal = "";
            literal += m_ch;
            return new_token(Token::TOKEN_ASTERISK, literal);
        }
        case '/':
        {
            string literal = "";
            literal += m_ch;
            return new_token(Token::TOKEN_SLASH, literal);
        }
        case '%':
        {
            string literal = "";
            literal += m_ch;
            return new_token(Token::TOKEN_MODULO, literal);
        }
        case '~':
        {
            string literal = "";
            literal += m_ch;
            return new_token(Token::TOKEN_TILDE, literal);
        }
        case '&':
        {
            string literal = "";
            literal += m_ch;
            return new_token(Token::TOKEN_BIT_AND, literal);
        }
        case '|':
        {
            string literal = "";
            literal += m_ch;
            return new_token(Token::TOKEN_BIT_OR, literal);
        }
        case '^':
        {
            string literal = "";
            literal += m_ch;
            return new_token(Token::TOKEN_BIT_XOR, literal);
        }
        case '<':
        {
            if (peek_char() == '<')
            {
                string literal;
                literal += m_ch;
                read_char();
                literal += m_ch;
                return new_token(Token::TOKEN_BIT_LSHIFT, literal);
            }
            else
            {
                string literal;
                literal += m_ch;
                read_char();
                literal += m_ch;
                return new_token(Token::TOKEN_ILLEGAL, literal);
            }
        }
        case '>':
        {
            if (peek_char() == '>')
            {
                string literal;
                literal += m_ch;
                read_char();
                literal += m_ch;
                return new_token(Token::TOKEN_BIT_RSHIFT, literal);
            }
            else
            {
                string literal;
                literal += m_ch;
                read_char();
                literal += m_ch;
                return new_token(Token::TOKEN_ILLEGAL, literal);
            }
        }
        case '(':
        {
            string literal;
            literal += m_ch;
            return new_token(Token::TOKEN_LPAREN, literal);
        }
        case ')':
        {
            string literal = "";
            literal += m_ch;
            return new_token(Token::TOKEN_RPAREN, literal);
        }

        case 0:
        {
            return new_token(Token::TOKEN_EOF, "");
        }
        default:
        {
            if (is_digit(m_ch))
            {
                string integer = read_number();
//                std::cout << is_digit(peek_char()) << std::endl;
                if (m_ch == '.' && is_digit(peek_char()))
                {
                    read_char();
                    string fraction = read_number();
                    unread_char();
                    return new_token(Token::TOKEN_FLOAT, integer + '.' + fraction);
                }
                unread_char();
                return new_token(Token::TOKEN_INTEGER, integer);
            }
            else if (is_letter(m_ch))
            {
                string literal = read_identifier();
                Token::Type type = Token::lookup(literal);
                unread_char();
                return new_token(type, literal);
            }
            else
            {
                string literal;
                literal += m_ch;
                return new_token(Token::TOKEN_ILLEGAL, literal);
            }
        }
    }
}