#pragma once
#include <ast/node.h>

namespace pi
{
    namespace ast
    {
        class Return : public Statement
        {
        public:
            Return() : Statement(Node::NODE_RETURN) {}
            ~Return() {}
            virtual Json json()
            {
                Json json;
                json["type"] = name();
                json["value"] = m_value ? m_value->json() : Json();
                return json;
            }
        public:
            std::shared_ptr<Expression> m_value;
        };
    }
}