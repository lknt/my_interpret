#pragma once
#include <ast/node.h>
#include <ast/block.h>

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
                for (auto & pair : m_pairs)
                {
                    Json elem;
                    elem["key"] = pair.first->json();
                    elem["value"] = pair.second->json();
                    pairs.append(elem);
                }
                json["pairs"] = pairs;

                return json;
            }
        public:
            std::map<std::shared_ptr<Expression>, std::shared_ptr<Expression>> m_pairs;
        };
    }
}