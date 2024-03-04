#pragma once
#include <ast/node.h>

namespace pi
{
    namespace ast
    {
        class Ternary : public Expression
        {
        public:
            Ternary() : Expression(Node::NODE_TERNARY) {}
            ~Ternary() {}
            virtual Json json()
            {
                Json json;
                json["type"] = name();
                json["condition"] = m_condition->json();
                json["if_true"] = m_if_true->json();
                json["if_false"] = m_if_false->json();
                return json;
            }
        public:
            std::shared_ptr<Expression> m_condition;
            std::shared_ptr<Expression> m_if_true;
            std::shared_ptr<Expression> m_if_false;
        };
    }
}