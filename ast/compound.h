#pragma once
#include <ast/node.h>

namespace pi
{
    namespace ast
    {
        class Compound : public Expression
        {
        public:
            Compound() : Expression(NODE_COMPOUND){}
            ~Compound() {}

            virtual Json json()
            {
                Json json;
                json["type"] = name();
                json["operator"] = m_operator;
                json["left"] = m_left->json();
                json["right"] = m_right->json();
                return json;
            }
        public:
            string m_operator;
            std::shared_ptr<Expression> m_left;
            std::shared_ptr<Expression> m_right;
        };
    }
}