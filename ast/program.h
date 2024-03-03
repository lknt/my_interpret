#pragma once

#include <ast/node.h>

namespace pi
{
    namespace ast
    {
        /*
         * Program类继承于Statement
         * 公有方法
         * 构造函数，NODE_PROGRAM
         * 析构函数
         * 公有成员变量
         * 一个列表，包含所有语句，即Expression_Statement
         *
         * */

        class Program : public Statement
        {
        public:
            Program() : Statement(NODE_PROGRAM){}
            ~Program(){}
            Json json()
            {
                Json json;
                json["type"] = name();
                Json statements;
                for (auto &stat : m_statement)
                {
                    statements.append(stat->json());
                }
                json["statements"] = statements;
                return json;
            }

        public:
            std::list<std::shared_ptr<Statement>> m_statement;
        };

    }
}