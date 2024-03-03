#pragma once
#include <ast/node.h>

namespace pi
{
    namespace ast {
        class Bool : public Expression
        {
        public:
            Bool() : Expression(NODE_BOOL) {}
            ~Bool() {}

            virtual Json json()
            {
                Json json;
                json["type"] = name();
                json["value"] = m_value ? "true" : "false";
                return json;
            }

        public:
            bool m_value;
        };
    }
}