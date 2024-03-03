//
// Created by ROG on 2024-03-01.
//
#pragma once
#include <ast/header.h>
using namespace pi::ast;

#include <object/header.h>
using namespace pi::object;


namespace pi
{
    namespace evaluator
    {
        /*
         * 对树进行递归下降并且求值
         * */

        class Evaluator
        {
        public:
            Evaluator() {}
            ~Evaluator() {}

            bool is_error(const std::shared_ptr<Object> &obj);
            std::shared_ptr<Object> new_error(const char * format, ...);
            std::shared_ptr<Object> new_integer(int64_t value);
            std::shared_ptr<Object> new_float(double value);
            std::shared_ptr<Object> cast_from_integer_to_float(const std::shared_ptr<Object> & obj);

            /*
             * 都是返回一个Object类型（Integer或者Error）
             * eval传入Node节点，
             * node->Expression
             * node->Statement->Expression_Statement(内含Expression智能指针
             * Statement->Program(内含一个包含Statement智能指针的list)
             *
             * eval_program是解析整个程序，eval是解析一个节点（一个Expression）
             * eval_integer只是解析一个integer节点
             * eval_infix解析中缀表达式
             * */
            std::shared_ptr<Object> eval(const std::shared_ptr<ast::Node> &node);
            std::shared_ptr<Object> eval_program(const std::list<std::shared_ptr<ast::Statement>>& stmt);
            std::shared_ptr<Object> eval_integer(const std::shared_ptr<ast::Integer> & node);
            std::shared_ptr<Object> eval_float(const std::shared_ptr<ast::Float> & node);


            std::shared_ptr<Object> eval_infix(const std::shared_ptr<ast::Infix> &right);
            std::shared_ptr<Object> eval_integer_infix_expression(const string &op, const std::shared_ptr<Object> & left, const std::shared_ptr<Object> & right);
            std::shared_ptr<Object> eval_float_infix_expression(const string &op, const std::shared_ptr<Object> & left, const std::shared_ptr<Object> & right);

            std::shared_ptr<Object> eval_prefix(const std::shared_ptr<ast::Prefix> &node);
            std::shared_ptr<Object> eval_minus_prefix_operator_expression(std::shared_ptr<Object> & right);
            std::shared_ptr<Object> eval_tilde_prefix_operator_expression(std::shared_ptr<Object> & right);
        };
    }
}