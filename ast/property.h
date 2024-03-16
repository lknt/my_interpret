#pragma once
#include <ast/node.h>

namespace pi
{
    namespace ast
    {
        class Property : public Expression
        {
        public:
            Property() : Expression(Node::NODE_PROPERTY) {}
            ~Property() {}
            virtual Json json()
            {
                Json json;
                json["type"] = name();
                json["object"] = m_object->json();
                json["property"] = m_property->json();
                return json;
            }
        public:
            std::shared_ptr<Expression> m_object;
            std::shared_ptr<Expression> m_property;
        };
    }
}