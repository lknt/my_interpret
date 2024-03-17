#pragma once
#include <ast/node.h>

namespace pi
{
    namespace ast {
        class Call : public Expression
        {
        public:
            Call() : Expression(NODE_CALL) {}
            ~Call() {}

            virtual Json json()
            {
                Json json;
                json["type"] = name();
                json["function"] = m_function->json();
                Json arguments;
                for (auto & arg : m_arguments)
                {
                    arguments.append(arg->json());

                }
                json["arguments"] = arguments;
                return json;
            }
        public:
            std::shared_ptr<Expression> m_function;
            std::vector<std::shared_ptr<Expression>> m_arguments;
        };
    }
}