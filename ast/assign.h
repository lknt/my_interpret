#pragma once
#include <ast/node.h>

namespace pi
{
    namespace ast {
        class Assign : public Expression
        {
        public:
            Assign() : Expression(NODE_ASSIGN) {}
            ~Assign() {}

            virtual Json json()
            {
                Json json;
                json["type"] = name();
                json["name"] = m_name->json();
                json["value"] = m_value->json();
                return json;
            }

        public:
            std::shared_ptr<Expression> m_name;
            std::shared_ptr<Expression> m_value;
        };
    }
}