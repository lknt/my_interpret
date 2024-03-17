#pragma once

#include <object/object.h>
#include <ast/block.h>
#include <ast/identifier.h>
using namespace pi::ast;
#include <evaluator/environment.h>
using namespace pi::evaluator;

namespace pi
{
    namespace object
    {
        class Function : public Object
        {
        public:
            Function() : Object(OBJECT_FUNCTION) {}
            ~Function() {}
            virtual string str() const
            {
                return "<function>";
            }
        public:
            std::vector<std::shared_ptr<Identifier>> m_parameters;
            std::map<string, std::shared_ptr<Expression>> m_defaults;
            std::shared_ptr<Block> m_body;
            Environment * m_env = nullptr;  // 指向外部作用域
        };
    }
}