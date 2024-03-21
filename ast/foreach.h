#pragma once
#include <ast/node.h>

namespace pi
{
    namespace ast
    {
        class Foreach : public Expression
        {
        public:
            Foreach() : Expression(NODE_FOREACH){}
            ~Foreach() {}

            virtual Json json()
            {
                Json json;
                json["type"] = name();
                json["key"] = m_key;
                json["value"] = m_value;
                json["expression"] = m_iterable->json();
                json["body"] = m_body->json();
                return json;
            }
        public:
            string m_key;
            string m_value;
            std::shared_ptr<Expression> m_iterable;
            std::shared_ptr<Block> m_body;
        };
    }
}