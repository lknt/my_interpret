#pragma once

#include <object/object.h>

namespace pi
{
    namespace object
    {
        class Float : public Object
        {
        public:
            Float() : Object(OBJECT_FLOAT), m_value(0) {}
            Float(double value) : Object(OBJECT_FLOAT), m_value(value) {}
            ~Float() {}
            virtual string str() const
            {
                return std::to_string(m_value);
            }

        public:
            double m_value;
        };
    }
}