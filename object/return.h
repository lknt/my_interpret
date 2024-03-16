#pragma once

#include <object/object.h>
#include <object/hashable.h>

namespace pi
{
    namespace object
    {
        class Return : public Object
        {
        public:
            Return() : Object(OBJECT_RETURN) {}
            ~Return() {}
            virtual string str() const
            {
                return m_value->str();
            }
        public:
            std::shared_ptr<Object> m_value;
        };
    }
}