#pragma once

#include <ast/node.h>

namespace pi
{
    namespace ast
    {
        /*
         * Integer类继承自Expression
         * 是一个整数是属于表达式的
         * 公有方法
         * 构造函数直接调用Expression的，type传NODE_INTEGER
         * 重写json函数，把type和value写进去
         * 公有成员变量
         * int64_t m_values;
         * */
        class Integer : public Expression
        {
        public:
            Integer() : Expression(NODE_INTEGER) {}
            Integer(int64_t m) : Expression(NODE_INTEGER), m_values(m){}
            ~Integer() {}

            Json json() override
            {
                Json json;
                json["type"] = name();
                json["value"] = std::to_string(m_values);
                return json;
            }
        public:
            int64_t m_values;
        };
    }
}