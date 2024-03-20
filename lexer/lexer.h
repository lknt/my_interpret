//
// Created by 19484 on 2024-02-24.
//

#pragma once

#include <string>
using std::string;

#include <token/token.h>
using namespace pi::token;

#include <fstream>
#include <sstream>
#include <iostream>

namespace pi
{
    namespace lexer
    {
        /*
         公有方法：
         一个词法解析器需要从文件中解析出token,所以需要有一个传入文件名字的构造函数,也需要析构函数
         next_token获取下一个token
         私有方法
         忽略空格 skip_white_space
         读取字符 read_char
         放回字符 unread_char
         是否为字母 is_digit
         读取数字 string read_number
         new一个新token   Token new_token(type, const string &literal)

         私有成员变量
         文件文本 string m_input
         当前字符 char m_ch
         当前位置 int m_pos
         下一位置 int m_next_pos
        */

        class Lexer
        {
        public:
            Lexer();
            Lexer(const string& file);
            Lexer(const char * buf, int len);
            ~Lexer() {}

            Token next_token();
        private:
            void skip_white_space();
            void read_char();
            char peek_char();
            void unread_char();
//            bool is_space(char ch) const;
            bool is_digit(char ch) const;
            bool is_letter(char ch) const;
            string read_number();
            string read_identifier();
            string read_single_quote_string();
            string read_double_quote_string();
            Token new_token(Token::Type type, const string & literal);

        public:
            string m_input;
            char m_ch;
            int m_pos;
            int m_next_pos;
            int m_line;
            int m_column;
        };
    }
}