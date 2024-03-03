#pragma once
#include <ast/node.h>

namespace pi
{
    namespace ast
    {
        class String : public Expression
        {
        public:
            String() : Expression(Node::NODE_STRING) {}
            ~String() {}
            virtual Json json()
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