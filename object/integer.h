#pragma once

#include <object/object.h>

namespace pi
{
    namespace object
    {
        class Integer : public Object
        {
        public:
            Integer() : Object(OBJECT_INTEGER), m_value(0) {}
            Integer(int64_t value) : Object(OBJECT_INTEGER), m_value(value) {}
            ~Integer() {}
            virtual string str()
            {
                return std::to_string(m_value);
            }

        public:
            int64_t m_value;
        };
    }
}