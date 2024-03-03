#pragma once
#include <ast/node.h>

namespace pi
{
    namespace ast
    {
        class Float : public Expression
        {
        public:
            Float() : Expression(NODE_FLOAT){}
            ~Float() {}

            virtual Json json()
            {
                Json json;
                json["type"] = name();
                json["value"] = std::to_string(m_values);
                return json;
            }
        public:
            double m_values;
        };
    }
}