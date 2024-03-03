#pragma once
#include <ast/node.h>


namespace pi
{
    namespace ast
    {
        class Prefix : public Expression
        {
        public:
            Prefix() : Expression(NODE_PREFIX) {}
            ~Prefix() {}
            virtual Json json() override
            {
                Json json;
                json["type"] = name();
                json["operator"] = m_operator;
                json["right"] = m_right->json();
                return json;
            }

        public:
            string m_operator;
            std::shared_ptr<Expression> m_right;
        };
    }
}