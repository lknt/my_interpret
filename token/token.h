//
// Created by 19484 on 2024-02-24.
//
#pragma once

#include <string>
#include <map>
#include <json/json.h>
#include <sstream>
using std::string;
using namespace yazi::json;


namespace pi
{
    namespace token
    {
        /*
         公有方法
         一个enum Type，定义所有类型的token
         有10种
         非法，eof，加减乘除，整形，左括号右括号，分号
         Token是词法分析的结果，它需要一个以(具体类型，文本)为参数的构造函数，析构函数
         返回token类型的type方法
         返回token类型对应的具体名字的name方法
         返回token字面量的literal方法
         show展示token的名字，字面量
         重载=运算符， 重载<<运算符
         json方法
         私有变量
         m_type,m_literal
         用来索引type名字的static  map<Type, string> m_name
         */
        class Token
        {
        public:
            enum Type
            {
                TOKEN_ILLEGAL = 0,
                TOKEN_INTEGER,
                TOKEN_FLOAT,
                TOKEN_EOF,
                TOKEN_PLUS,
                TOKEN_MINUS,
                TOKEN_ASTERISK,
                TOKEN_SLASH,
                TOKEN_MODULO,
                TOKEN_TILDE,
                TOKEN_BIT_AND,
                TOKEN_BIT_OR,      //|
                TOKEN_BIT_XOR,     //^
                TOKEN_BIT_LSHIFT,  // <<
                TOKEN_BIT_RSHIFT, // >>
                TOKEN_LT,  // <
                TOKEN_GT,  // >
                TOKEN_GE,  // >=
                TOKEN_LE,  // <=
                TOKEN_NE,  // !=
                TOKEN_EQ,  //==

                TOKEN_AND, //&&
                TOKEN_OR, //||
                TOKEN_NOT,  // !

                TOKEN_LPAREN,
                TOKEN_RPAREN,
                TOKEN_SEMICOLON,
                TOKEN_IDENTIFIER,
                TOKEN_TRUE,   //true
                TOKEN_FALSE,  //false
                TOKEN_STRING,

                TOKEN_NULL,
                TOKEN_ASSIGN,

                TOKEN_PLUS_ASSIGN,
                TOKEN_MINUS_ASSIGN,
                TOKEN_ASTERISK_ASSIGN,
                TOKEN_SLASH_ASSIGN,
                TOKEN_MODULO_ASSIGN,
                TOKEN_BIT_OR_ASSIGN,
                TOKEN_BIT_AND_ASSIGN,
                TOKEN_BIT_XOR_ASSIGN,
                TOKEN_BIT_LSHIFT_ASSIGN,
                TOKEN_BIT_RSHIFT_ASSIGN,

                TOKEN_INCREASE,
                TOKEN_DECREASE,

                TOKEN_QUESTION,
                TOKEN_COLON,
                TOKEN_IF,
                TOKEN_ELSE,
                TOKEN_LBRACE,
                TOKEN_RBRACE,

                TOKEN_BREAK,
                TOKEN_CONTINUE,
                TOKEN_WHILE,

                TOKEN_FOR,

                TOKEN_SWITCH,
                TOKEN_CASE,
                TOKEN_DEFAULT,

                TOKEN_COMMA,

                TOKEN_LBRACKET,
                TOKEN_RBRACKET,

                TOKEN_DOT,

                TOKEN_IN,

                TOKEN_FUNCTION,
                TOKEN_RETURN,
            };

            Token();
            Token(Type type, const string& literal, int line, int column);

            Type type() const;
            string name() const;
            string literal() const;

            int line() const;
            int column() const;

            string show() const;
            Json json() const;

            Token & operator=(const Token &other);
            static Type lookup(const string & identifier);
            friend std::ostream & operator<<(std::ostream& out, const Token tk)
            {
                out << tk.show() << " ";
                return out;
            }
        private:
            Type m_type;
            string m_literal;
            int m_column;
            int m_line;
        public:
            static std::map<Type, string> m_name;
            static std::map<string, Type> m_keywords;

        };


    }
}

