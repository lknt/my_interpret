#pragma once
#include <ast/node.h>

namespace pi
{
    namespace ast {
        class Break : public Statement
        {
        public:
            Break() : Statement(NODE_BREAK) {}
            ~Break() {}

            virtual Json json()
            {
                Json json;
                json["type"] = name();
                return json;
            }

        };
    }
}