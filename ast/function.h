#pragma once
#include <ast/node.h>

namespace pi
{
    namespace ast
    {
        class Function : public Expression
        {
        public:
            Function() : Expression(Node::NODE_FUNCTION) {}
            ~Function() {}
            virtual Json json()
            {
                Json json;
                json["type"] = name();
                Json parameters;
                for (auto & param : m_parameters)
                {
                    parameters.append(param->json());
                }
                json["parameters"] = parameters;
                json["body"] = m_body->json();
                return json;
            }
        public:
            std::vector<std::shared_ptr<Identifier>> m_parameters;
            std::shared_ptr<Block> m_body;
        };
    }
}