#pragma once

#include <token/token.h>
using namespace pi::token;
#include <cstdint>
#include <memory>
#include <list>

namespace pi
{
    namespace ast
    {
        /*
         * node作为ast的基类
         * 公有方法
         * enum Type，其中有整形节点，中缀节点，表达式语句，程序（是一组语句）
         * 构造函数，其中一个可以直接传入type构造
         * 析构函数，声明为virtual
         * 返回节点类型 Type type
         * 返回名字 string name
         * 虚函数Json json，用于生成json文件
         * 公有成员变量
         * Type m_type
         * Token m_token
         * std::map<Type type, string> m_names;
         * */
        class Node
        {
        public:
            enum Type
            {
                NODE_INTEGER = 0,
                NODE_FLOAT,
                NODE_BOOL,
                NODE_INFIX,
                NODE_EXPRESSION_STATEMENT,
                NODE_PROGRAM,
                NODE_PREFIX,
            };
            Node() {}
            Node(Type type) : m_type(type){}
            virtual ~Node() {}

            Type type() const {return m_type;}
            string name() const;

            virtual Json json() = 0;
        public:
            Type m_type;
            Token m_token;
            static std::map<Type, string> m_names;
        };
        /*
         * 语句和表达式都继承于Node，只需要构造函数和析构函数即可
         * */
        class Expression : public Node
        {
        public:
            Expression() : Node(){}
            Expression(Type type) : Node(type) {}
            ~Expression() {}
        };

        class Statement : public Node
        {
        public:
            Statement() : Node(){}
            Statement(Type type) : Node(type) {}
            ~Statement() {}
        };
    }
}