#pragma once
#include <ast/node.h>


namespace pi
{
    namespace ast
    {
        class Postfix : public Expression
        {
        public:
            Postfix() : Expression(NODE_POSTFIX) {}
            ~Postfix() {}
            virtual Json json() override
            {
                Json json;
                json["type"] = name();
                json["operator"] = m_operator;
                json["left"] = m_left->json();
                return json;
            }

        public:
            string m_operator;
            std::shared_ptr<Expression> m_left;
        };
    }
}