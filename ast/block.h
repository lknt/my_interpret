#pragma once
#include <ast/node.h>

namespace pi
{
    namespace ast {
        class Block : public Expression
        {
        public:
            Block() : Expression(NODE_BLOCK) {}
            ~Block() {}

            virtual Json json()
            {
                Json json;
                json["type"] = name();
                Json statements;
                for (auto stmt : m_statements)
                {
                    statements.append(stmt->json());
                }
                json["statements"] = statements;
                return json;
            }

        public:
            std::list<std::shared_ptr<Statement>> m_statements;
        };
    }
}