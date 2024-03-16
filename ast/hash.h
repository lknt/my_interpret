#pragma once
#include <ast/node.h>

namespace pi
{
    namespace ast
    {

        class Hash : public Expression
        {
        public:
            Hash() : Expression(NODE_HASH){}
            ~Hash() {}

            virtual Json json()
            {
                Json json;
                json["type"] = name();
                Json pairs;
                for (auto & p : m_pairs)
                {
                    Json elem;
//                    printf("%p\n",pair.first.get());
//                    auto lit = std::dynamic_pointer_cast<ast::Integer>(pair.second);
//                    printf("%d\n", lit->m_values);
                    elem["key"] = p.first->json();
                    elem["value"] = p.second->json();
                    pairs.append(elem);
                }
                json["pairs"] = pairs;

                return json;
            }
        public:
            std::vector<std::pair<std::shared_ptr<Expression>, std::shared_ptr<Expression>>> m_pairs;
        };
    }
}