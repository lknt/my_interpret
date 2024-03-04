#pragma once

#include <ast/node.h>

namespace pi
{
    namespace ast
    {
        /*
         * 这里只存储变量名字*/
        class Identifier : public Expression
        {
        public:
            Identifier() : Expression(NODE_IDENTIFIER) {}
//            Identifier(int64_t m) : Expression(NODE_IDENTIFIER), m_value(m){}
            ~Identifier() {}

            Json json() override
            {
                Json json;
                json["type"] = name();
                json["value"] = m_value;
                return json;
            }
        public:
            string m_value;
        };
    }
}