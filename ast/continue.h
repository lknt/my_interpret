#pragma once
#include <ast/node.h>

namespace pi
{
    namespace ast {
        class Continue : public Statement
        {
        public:
            Continue() : Statement(NODE_CONTINUE) {}
            ~Continue() {}

            virtual Json json()
            {
                Json json;
                json["type"] = name();
                return json;
            }

        };
    }
}