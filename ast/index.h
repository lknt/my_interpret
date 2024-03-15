#pragma once

#include <ast/node.h>

namespace pi
{
    namespace ast
    {
        /*
         * 这里只存储变量名字*/
        class Index : public Expression
        {
        public:
            Index() : Expression(NODE_INDEX) {}
            ~Index() {}

            Json json() override
            {
                Json json;
                json["type"] = name();
                json["left"] = m_left->json();
                json["index"] = m_index->json();
                return json;
            }
        public:
            std::shared_ptr<Expression> m_left;
            std::shared_ptr<Expression> m_index;
        };
    }
}