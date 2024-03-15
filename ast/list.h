#pragma once
#include <ast/node.h>

namespace pi
{
    namespace ast
    {
        class List : public Expression
        {
        public:
            List() : Expression(Node::NODE_LIST) {}
            ~List() {}
            virtual Json json()
            {
                Json json;
                json["type"] = name();
                Json elements;
                for (auto & elem : m_elements)
                {
                    elements.append(elem->json());
                }
                json["elements"] = elements;
                return json;
            }

        public:
            std::vector<std::shared_ptr<Expression>> m_elements;

        };
    }
}