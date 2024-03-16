#pragma once

#include <ast/node.h>

namespace pi
{
    namespace ast
    {
        class In : public Expression
        {
        public:
            In() : Expression(NODE_IN) {}

            ~In() {}

            Json json() override
            {
                Json json;
                json["type"] = name();
                json["left"] = m_left->json();
                json["right"] = m_right->json();
                return json;
            }
        public:
            std::shared_ptr<Expression> m_left;
            std::shared_ptr<Expression> m_right;
        };
    }
}