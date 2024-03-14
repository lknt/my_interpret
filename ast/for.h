#pragma once
#include <ast/node.h>
#include <ast/block.h>

namespace pi
{
    namespace ast
    {
        class For : public Expression
        {
        public:
            For() : Expression(NODE_FOR){}
            ~For() {}

            virtual Json json()
            {
                Json json;
                json["type"] = name();
                json["starter"] = m_starter->json();
                json["condition"] = m_condition->json();
                json["closer"] = m_closer->json();
                json["body"] = m_body->json();
                return json;
            }
        public:
            std::shared_ptr<Expression> m_starter;
            std::shared_ptr<Expression> m_condition;
            std::shared_ptr<Expression> m_closer;
            std::shared_ptr<Block> m_body;
        };
    }
}