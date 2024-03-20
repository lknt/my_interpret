#pragma once
#include <ast/node.h>

namespace pi
{
    namespace ast
    {
        class Method : public Expression
        {
        public:
            Method() : Expression(Node::NODE_METHOD) {}
            ~Method() {}
            virtual Json json()
            {
                Json json;
                json["type"] = name();
                json["object"] = m_object->json();
                json["method"] = m_method->json();
                Json arguments;
                for (auto & arg : m_arguments)
                {
                    arguments.append(arg->json());
                }
                json["arguments"] = arguments;
                return json;
            }

        public:
            std::shared_ptr<Expression> m_object;
            std::shared_ptr<Expression> m_method;
            std::vector<std::shared_ptr<Expression>> m_arguments;
        };
    }
}