//
// Created by 19484 on 2024-02-25.
//

#pragma once

#include <ast/header.h>
#include <lexer/lexer.h>

using namespace pi::ast;
using namespace pi::lexer;

namespace pi
{
    namespace parser
    {
        /*
         * Parser是解析器，负责从文件中解析出ast，需要lexer的帮助，基础是ast中的基本类型
         * 公有方法
         * enum Precedence设置优先级，分三种，最低，和，积
         * 构造函数，有一个是以lexer指针为参数构造
         * 析构函数
         * 定义两个typedef，函数指针
         * 都是返回std::shared_ptr<Expression>
         * 一个是prefix_parser_fn
         * 一个是infix_parser_fn,有一个参数是一个Expresion的智能指针
         * void next_token()
         * 询问现在的token和之后的token是否为给定类型
         * bool curr_token_is(Type type);
         * bool peek_token_is(Type type);
         *
         * 一个错误处理函数
         * void no_prefix_parse_fn_errors();
         * 返回错误链表的函数
         * std::list<string>& errors();
         *
         * 解析表达式
         * 返回Expression指针，传入优先级
         * std::shared_ptr<Expression> parse_expression(int precedence);
         *
         * 返回Program指针
         * std::shared_ptr<Program> parse_program();
         * 返回Statement指针
         * std::shared_ptr<Statement> parse_statement()
         * 返回表达式语句指针
         * std::shared_ptr<Expression_Statement> parse_expression_statement();
         *
         * 前缀解析
         * 解析整形
         * std::shared_ptr<Expression> parse_integer();
         * 解析括号表达式
         * std::shared_ptr<Expression> parse_group();
         *
         * 中缀解析
         * 传入一个Expression指针
         * 返回Expression指针
         *
         * 私有成员变量
         * lexer指针m_lexer
         * Token m_curr, m_peek;
         * std::list<string> m_errors;
         * 三个map
         * 对应于，查找对应token type的优先级m_precedences
         * 对应于token type的前缀解析函数m_prefix_parser_fns
         * 对应于token type的中缀解析函数m_infix_parser_fns
         * */
        class Parser
        {
        public:
            enum Precedence
            {
                LOWEST = 0,
                SUM,   // + -
                PRODUCT, // *  /  %
                PREFIX, // -a  ~a  !a
            };
            Parser();
            Parser(std::shared_ptr<Lexer>& lexer);
            ~Parser();

            typedef std::shared_ptr<Expression> (Parser::*prefix_parser_fn)(void);
            typedef std::shared_ptr<Expression> (Parser::*infix_parser_fn)(const std::shared_ptr<Expression>&);

            void next_token();

            bool curr_token_is(Token::Type type);
            bool peek_token_is(Token::Type type);
            bool expect_peek_token(Token::Type type);
            void peek_error(Token::Type type);

            int curr_token_precedence();
            int peek_token_precedence();

            void no_prefix_parse_fn_error(Token::Type type);

            std::list<string> & errors();

            std::shared_ptr<Expression> parse_expression(int precedence);


            std::shared_ptr<Program> parse_program();
            std::shared_ptr<Statement> parse_statement();
            std::shared_ptr<Expression_Statement> parse_expression_statement();



            //prefix
            std::shared_ptr<Expression> parse_integer();
            std::shared_ptr<Expression> parse_float();
            std::shared_ptr<Expression> parse_group();
            std::shared_ptr<Expression> parse_prefix();

            //infix
            std::shared_ptr<Expression> parse_infix(const std::shared_ptr<Expression>&);

        private:

            std::shared_ptr<Lexer> m_lexer;
            Token m_curr;
            Token m_peek;
            std::list<string> m_errors;

            static std::map<Token::Type, int> m_precedences;
            static std::map<Token::Type, prefix_parser_fn> m_prefix_parser_fns;
            static std::map<Token::Type, infix_parser_fn> m_infix_parser_fns;



        };
    }
}