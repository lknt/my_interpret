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
    m_line = 1;
    m_column = 0;
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
    m_line = 1;
    m_column = 0;
}

Lexer::Lexer(const char *buf, int len) {
    m_ch = 0;
    m_pos = 0;
    m_next_pos = 0;
    m_input.assign(buf, len);
    m_line = 1;
    m_column = 0;
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
        if (m_ch == '\n')
        {
            m_line ++;
            m_column = 0;
        }
        else if (m_ch == ' ')
        {
            m_column ++;
        }
        else if (m_ch == '\t')
        {
            m_column += 4;
        }
        read_char();
    }
}

//bool Lexer::is_space(char ch) const
//{
//    return ch == ' ' || ch == '\t' || ch == '\n';
//}

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
    Token token(type, literal, m_line, m_column);
    m_column += (int)literal.length();
    if (type == Token::TOKEN_STRING)
    {
        m_column += 2;
    }
    return token;
}

string Lexer::read_single_quote_string()
{
    string str;
    while(true)
    {
        read_char();
        if (m_ch == '\'' || m_ch == 0)
        {
            break;
        }
        /*
         * 对'转义*/
        else if (m_ch == '\\' && peek_char() == '\'')
        {
            read_char();
        }
        str += m_ch;
    }
    return str;
}

string Lexer::read_double_quote_string() {
    string str;
    while(true)
    {
        read_char();
        if (m_ch == '"' || m_ch == 0)
        {
            break;
        }
            /*
             * 对'转义*/
        else if (m_ch == '\\')
        {
            switch (peek_char()) {
                case 'n':
                    read_char();
                    m_ch = '\n';
                    break;
                case 'r':
                    read_char();
                    m_ch = '\r';
                    break;
                case 't':
                    read_char();
                    m_ch = '\t';
                    break;
                case '"':
                    read_char();
                    m_ch = '"';
                    break;
                case '\\':
                    read_char();
                    m_ch = '\\';
                    break;
                    /*到这里无需省略转义符号*/
                default:
                    break;
            }
        }
        str += m_ch;
    }
    return str;
}
//
Token Lexer::next_token() {
    read_char();
    skip_white_space();
    switch(m_ch)
    {
        case '+':
        {
            if (peek_char() == '=')
            {
                string literal;
                literal += m_ch;
                read_char();
                literal += m_ch;
                return new_token(Token::TOKEN_PLUS_ASSIGN, literal);
            }
            else if (peek_char() == '+')
            {
                string literal;
                literal += m_ch;
                read_char();
                literal += m_ch;
                return new_token(Token::TOKEN_INCREASE, literal);
            }
            else
            {
                string literal;
                literal += m_ch;
                return new_token(Token::TOKEN_PLUS, literal);
            }
        }
        case '-':
        {
            if (peek_char() == '=')
            {
                string literal;
                literal += m_ch;
                read_char();
                literal += m_ch;
                return new_token(Token::TOKEN_MINUS_ASSIGN, literal);
            }
            else if (peek_char() == '-')
            {
                string literal;
                literal += m_ch;
                read_char();
                literal += m_ch;
                return new_token(Token::TOKEN_DECREASE, literal);
            }
            else {
                string literal;
                literal += m_ch;
                return new_token(Token::TOKEN_MINUS, literal);
            }
        }
        case '*':
        {
            if (peek_char() == '=')
            {
                string literal;
                literal += m_ch;
                read_char();
                literal += m_ch;
                return new_token(Token::TOKEN_ASTERISK_ASSIGN, literal);
            }
            else {
                string literal = "";
                literal += m_ch;
                return new_token(Token::TOKEN_ASTERISK, literal);
            }
        }
        case '/':
        {
            if (peek_char() == '=')
            {
                string literal;
                literal += m_ch;
                read_char();
                literal += m_ch;
                return new_token(Token::TOKEN_SLASH_ASSIGN, literal);
            }
            else if (peek_char() == '/')
            {
                skip_single_line_comment();
                return next_token();
            }
            else if (peek_char() == '*')
            {
                skip_multi_line_comment();
                return next_token();
            }
            else
            {
                string literal;
                literal += m_ch;
                return new_token(Token::TOKEN_SLASH, literal);
            }
        }
        case '%':
        {
            if (peek_char() == '=')
            {
                string literal;
                literal += m_ch;
                read_char();
                literal += m_ch;
                return new_token(Token::TOKEN_MODULO_ASSIGN, literal);
            }
            else {
                string literal = "";
                literal += m_ch;
                return new_token(Token::TOKEN_MODULO, literal);
            }
        }
        case '~':
        {
            string literal = "";
            literal += m_ch;
            return new_token(Token::TOKEN_TILDE, literal);
        }
        case '&':
        {
            if (peek_char() == '&')
            {
                string literal;
                literal += m_ch;
                read_char();
                literal += m_ch;
                return new_token(Token::TOKEN_AND, literal);
            }
            else if (peek_char() == '=')
            {
                string literal;
                literal += m_ch;
                read_char();
                literal += m_ch;
                return new_token(Token::TOKEN_BIT_AND_ASSIGN, literal);
            }
            else {
                string literal;
                literal += m_ch;
                return new_token(Token::TOKEN_BIT_AND, literal);
            }

        }
        case '|':
        {
            if (peek_char() == '|')
            {
                string literal;
                literal += m_ch;
                read_char();
                literal += m_ch;
                return new_token(Token::TOKEN_OR, literal);
            }
            else if (peek_char() == '=')
            {
                string literal;
                literal += m_ch;
                read_char();
                literal += m_ch;
                return new_token(Token::TOKEN_BIT_OR_ASSIGN, literal);
            }
            else {
                string literal;
                literal += m_ch;
                return new_token(Token::TOKEN_BIT_OR, literal);
            }
        }
        case '^':
        {
            if (peek_char() == '=')
            {
                string literal;
                literal += m_ch;
                read_char();
                literal += m_ch;
                return new_token(Token::TOKEN_BIT_XOR_ASSIGN, literal);
            }
            else
            {
                string literal = "";
                literal += m_ch;
                return new_token(Token::TOKEN_BIT_XOR, literal);
            }
        }
        case '<':
        {
            if (peek_char() == '<')
            {
                string literal;
                literal += m_ch;
                read_char();
                literal += m_ch;
                if (peek_char() == '=')
                {
                    read_char();
                    literal += m_ch;
                    return new_token(Token::TOKEN_BIT_LSHIFT_ASSIGN, literal);
                }
                else
                {
                    return new_token(Token::TOKEN_BIT_LSHIFT, literal);
                }
            }
            else if (peek_char() == '=')
            {
                string literal;
                literal += m_ch;
                read_char();
                literal += m_ch;
                return new_token(Token::TOKEN_LE, literal);
            }
            else
            {
                string literal;
                literal += m_ch;
                return new_token(Token::TOKEN_LT, literal);
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
                if (peek_char() == '=')
                {
                    read_char();
                    literal += m_ch;
                    return new_token(Token::TOKEN_BIT_RSHIFT_ASSIGN, literal);
                }
                else {
                    return new_token(Token::TOKEN_BIT_RSHIFT, literal);
                }
            }
            else if (peek_char() == '=')
            {
                string literal;
                literal += m_ch;
                read_char();
                literal += m_ch;
                return new_token(Token::TOKEN_GE, literal);
            }
            else
            {
                string literal;
                literal += m_ch;
                return new_token(Token::TOKEN_GT, literal);
            }
        }
        case '=':
        {
            if (peek_char() == '=')
            {
                string literal;
                literal += m_ch;
                read_char();
                literal += m_ch;
                return new_token(Token::TOKEN_EQ, literal);
            }
            else
            {
                string literal;
                literal += m_ch;
                return new_token(Token::TOKEN_ASSIGN, literal);
            }
        }

        case '!':
        {
            if (peek_char() == '=')
            {
                string literal;
                literal += m_ch;
                read_char();
                literal += m_ch;
                return new_token(Token::TOKEN_NE, literal);
            }
            else
            {
                string literal;
                literal += m_ch;
                return new_token(Token::TOKEN_NOT, literal);
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
        case '{':
        {
            string literal;
            literal += m_ch;
            return new_token(Token::TOKEN_LBRACE, literal);
        }
        case '}':
        {
            string literal = "";
            literal += m_ch;
            return new_token(Token::TOKEN_RBRACE, literal);
        }
        case '\'':
        {
            string literal;
            literal += m_ch;
            return new_token(Token::TOKEN_STRING, read_single_quote_string());
        }
        case '\"':
        {
            string literal;
            literal += m_ch;
            return new_token(Token::TOKEN_STRING, read_double_quote_string());
        }
        case '?':
        {
            string literal;
            literal += m_ch;
            return new_token(Token::TOKEN_QUESTION, literal);

        }
        case ':':
        {
            string literal;
            literal += m_ch;
            return new_token(Token::TOKEN_COLON, literal);

        }
        case ';':
        {
            string literal;
            literal += m_ch;
            return new_token(Token::TOKEN_SEMICOLON, literal);
        }
        case ',':
        {
            string literal;
            literal += m_ch;
            return new_token(Token::TOKEN_COMMA, literal);
        }
        case '[':
        {
            string literal;
            literal += m_ch;
            return new_token(Token::TOKEN_LBRACKET, literal);
        }
        case ']':
        {
            string literal;
            literal += m_ch;
            return new_token(Token::TOKEN_RBRACKET, literal);
        }
        case '.':
        {
            string literal;
            literal += m_ch;
            return new_token(Token::TOKEN_DOT, literal);
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


void Lexer::skip_single_line_comment()
{
    read_char();
    while (true)
    {
        read_char();
        if (m_ch == '\n' || m_ch == '\r' || m_ch == 0)
        {
            break;
        }
    }
    m_line += 1;
    m_column = 1;
}

void Lexer::skip_multi_line_comment()
{
    read_char();
    while (true)
    {
        read_char();
        if (m_ch == 0)
        {
            break;
        }
        else if (m_ch == '\n')
        {
            m_line += 1;
            m_column = 1;
        }
        else if (m_ch == '*' && peek_char() == '/')
        {
            read_char();
            break;
        }
    }
}
