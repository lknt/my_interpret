#pragma once

#include <ast/node.h>

namespace pi
{
    namespace ast
    {
        /*
         * Expression_Statement是表达式语句，继承于Statement
         * 公有方法
         * 构造函数，NODE_EXPRESSION
         * 析构函数
         * json重写
         * 公有成员变量
         * m_expression
         * */

        class Expression_Statement : public Statement
        {
        public:
            Expression_Statement() : Statement(NODE_EXPRESSION_STATEMENT){}
            ~Expression_Statement() {}
            Json json()
            {
                Json json;
                json["type"] = name();
                json["expresion"] = m_expression->json();
                return json;
            }

        public:
            std::shared_ptr<Expression> m_expression;

        };
    }
}