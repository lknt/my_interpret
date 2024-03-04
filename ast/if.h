#pragma once
#include <ast/block.h>

namespace pi
{
    namespace ast {
        class Scenario : public Expression
        {
        public:
            Scenario() : Expression(NODE_SCENARIO) {}
            ~Scenario() {}
            virtual Json json()
            {
                Json json;
                json["type"] = name();
                json["condition"] = m_condition->json();
                json["body"] = m_body->json();
                return json;
            }
        public:
            std::shared_ptr<Expression> m_condition;
            std::shared_ptr<Block> m_body;
        };

        class If : public Expression
        {
        public:
            If() : Expression(NODE_IF) {}
            ~If() {}

            virtual Json json()
            {
                Json json;
                json["type"] = name();
                Json scenarios;
                for (auto & scenario : m_scenarios)
                {
                    scenarios.append(scenario->json());
                }
                json["scenarios"] = scenarios;
                return json;
            }
        public:
            std::list<std::shared_ptr<Scenario>> m_scenarios;
        };
    }
}