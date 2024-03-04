#pragma once
#include <ast/node.h>

namespace pi
{
    namespace ast
    {
        class Null : public Expression
        {
        public:
            Null() : Expression(Node::NODE_NULL) {}
            ~Null() {}
            virtual Json json()
            {
                Json json;
                json["type"] = name();
                json["value"] = "null";
                return json;
            }
        };
    }
}