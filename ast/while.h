#pragma once
#include <ast/node.h>
#include <ast/block.h>

namespace pi
{
    namespace ast {
        class While : public Expression
        {
        public:
            While() : Expression(NODE_WHILE) {}
            ~While() {}

            virtual Json json()
            {
                Json json;
                json["type"] = name();
                json["condition"] = m_condition->json();
                json["body"] = m_body->json();
                return json;
            }
        public:
            std::shared_ptr<Expression> m_condition;
            std::shared_ptr<Block> m_body;
        };
    }
}