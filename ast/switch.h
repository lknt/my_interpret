#pragma once
#include <ast/node.h>
#include <ast/block.h>


namespace pi
{
    namespace ast
    {
        class Case : public Expression
        {
        public:
            Case() : Expression(Node::NODE_CASE) {}
            ~Case() {}
            virtual Json json()
            {
                Json json;
                json["type"] = name();
                Json values;

                for (auto &val : m_values)
                {
                    values.append(val->json());
                }

                json["values"] = values;
                json["body"] = m_body->json();
                json["default"] = m_default ? "true" : "false";

                return json;
            }
        public:
            std::list<std::shared_ptr<Expression>> m_values;
            std::shared_ptr<Block> m_body;
            bool m_default = false;
        };

        class Switch : public Expression
        {
        public:
            Switch() : Expression(Node::NODE_SWITCH) {}
            ~Switch() {}
            virtual Json json()
            {
                Json json;
                json["type"] = name();
                json["value"] = m_value->json();
                Json cases;
                for (auto &elem : m_cases)
                {
                    cases.append(elem->json());
                }
                json["cases"] = cases;
//                printf("finish switch");
                return json;
            }
        public:
            std::shared_ptr<Expression> m_value;
            std::list<std::shared_ptr<Case>> m_cases;
        };
    }
}