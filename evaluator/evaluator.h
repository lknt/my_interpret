//
// Created by ROG on 2024-03-01.
//
#pragma once
#include <ast/header.h>
using namespace pi::ast;

#include <object/header.h>
using namespace pi::object;

#include <evaluator/environment.h>


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
            bool is_true(const std::shared_ptr<Object> &obj);
            std::shared_ptr<Object> new_error(const char * format, ...);
            std::shared_ptr<Object> new_integer(int64_t value);
            std::shared_ptr<Object> new_float(double value);
            std::shared_ptr<Object> new_bool(bool value);
            std::shared_ptr<Object> new_string(string value);
            std::shared_ptr<Object> new_null();
            std::shared_ptr<Object> new_break();
            std::shared_ptr<Object> new_continue();
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
            std::shared_ptr<Object> eval(const std::shared_ptr<ast::Node> &node, Environment * env);
            std::shared_ptr<Object> eval_program(const std::list<std::shared_ptr<ast::Statement>>& stmt, Environment * env);
            std::shared_ptr<Object> eval_integer(const std::shared_ptr<ast::Integer> & node);
            std::shared_ptr<Object> eval_float(const std::shared_ptr<ast::Float> & node);
            std::shared_ptr<Object> eval_bool(const std::shared_ptr<ast::Bool> & node);
            std::shared_ptr<Object> eval_string(const std::shared_ptr<ast::String> & node);
            std::shared_ptr<Object> eval_identifier(const std::shared_ptr<ast::Identifier> & node, Environment * env);
            std::shared_ptr<Object> eval_assign(const std::shared_ptr<ast::Assign> & node, Environment * env);
            std::shared_ptr<Object> eval_compound(const std::shared_ptr<ast::Compound> & node, Environment * env);
            std::shared_ptr<Object> eval_ternary(const std::shared_ptr<ast::Ternary> & node, Environment * env);
            std::shared_ptr<Object> eval_block(const std::shared_ptr<ast::Block> & node, Environment * env);
            std::shared_ptr<Object> eval_if(const std::shared_ptr<ast::If> & node, Environment * env);
            std::shared_ptr<Object> eval_break(const std::shared_ptr<ast::Break> & node);
            std::shared_ptr<Object> eval_continue(const std::shared_ptr<ast::Continue> & node);
            std::shared_ptr<Object> eval_while(const std::shared_ptr<ast::While> & node, Environment * env);
            std::shared_ptr<Object> eval_for(const std::shared_ptr<ast::For> & node, Environment * env);
            std::shared_ptr<Object> eval_switch(const std::shared_ptr<ast::Switch> & node, Environment * env);
            std::shared_ptr<Object> eval_list(const std::shared_ptr<ast::List> & node, Environment * env);
            std::shared_ptr<Object> eval_hash(const std::shared_ptr<ast::Hash> & node, Environment * env);



            std::shared_ptr<Object> eval_null();

            std::shared_ptr<Object> eval_infix(const string &op, const std::shared_ptr<Object> & left, const std::shared_ptr<Object> & right, Environment * env);
            std::shared_ptr<Object> eval_integer_infix_expression(const string &op, const std::shared_ptr<Object> & left, const std::shared_ptr<Object> & right);
            std::shared_ptr<Object> eval_float_infix_expression(const string &op, const std::shared_ptr<Object> & left, const std::shared_ptr<Object> & right);
            std::shared_ptr<Object> eval_bool_infix_expression(const string &op, const std::shared_ptr<Object> & left, const std::shared_ptr<Object> & right);
            std::shared_ptr<Object> eval_string_infix_expression(const string &op, const std::shared_ptr<Object> & left, const std::shared_ptr<Object> & right);
            std::shared_ptr<Object> eval_string_integer_infix_expression(const string &op, const std::shared_ptr<Object> & left, const std::shared_ptr<Object> & right);
            std::shared_ptr<Object> eval_null_infix_expression(const string &op, const std::shared_ptr<Object> & left, const std::shared_ptr<Object> & right);
            std::shared_ptr<Object> eval_diff_type_operator_expression(const string &op, const std::shared_ptr<Object> & left, const std::shared_ptr<Object> & right);
            std::shared_ptr<Object> eval_list_infix_expression(const string &op, const std::shared_ptr<Object> & left, const std::shared_ptr<Object> & right);
            std::shared_ptr<Object> eval_list_integer_infix_expression(const string &op, const std::shared_ptr<Object> & left, const std::shared_ptr<Object> & right);

            //index
            std::shared_ptr<Object> eval_index_expression(const std::shared_ptr<ast::Index> & node, Environment * env);
            std::shared_ptr<Object> eval_list_index_expression(const std::shared_ptr<Object> & left, const std::shared_ptr<Object> & index);
            std::shared_ptr<Object> eval_string_index_expression(const std::shared_ptr<Object> & left, const std::shared_ptr<Object> & index);
            std::shared_ptr<Object> eval_hash_index_expression(const std::shared_ptr<Object> & left, const std::shared_ptr<Object> & index);

            //index assign
            std::shared_ptr<Object> eval_index_assignment(const std::shared_ptr<ast::Index> & name, const std::shared_ptr<Object> & val, Environment * env);
            //给列表相应位置赋值
            std::shared_ptr<Object> eval_list_index_assignment(const std::shared_ptr<Object> & name, const std::shared_ptr<Object> & index, const std::shared_ptr<Object> & val);
            std::shared_ptr<Object> eval_hash_index_assignment(const std::shared_ptr<Object> & name, const std::shared_ptr<Object> & index, const std::shared_ptr<Object> & val);


            std::shared_ptr<Object> eval_prefix(const std::shared_ptr<ast::Prefix> &node, Environment * env);
            std::shared_ptr<Object> eval_minus_prefix_operator_expression(std::shared_ptr<Object> & right);
            std::shared_ptr<Object> eval_tilde_prefix_operator_expression(std::shared_ptr<Object> & right);
            std::shared_ptr<Object> eval_bang_prefix_operator_expression(std::shared_ptr<Object> & right);

            std::shared_ptr<Object> eval_postfix(const std::shared_ptr<ast::Postfix> &node, Environment * env);

        };
    }
}