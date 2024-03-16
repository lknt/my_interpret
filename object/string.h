#pragma once

#include <object/object.h>
#include <object/hashable.h>

namespace pi
{
    namespace object
    {
        class String : public Object, public Hashable
        {
        public:
            String() : Object(OBJECT_STRING) {}
            String(string & value) : Object(OBJECT_STRING), m_value(value) {}
            ~String() {}
            virtual string str() const
            {
                return m_value;
            }
            virtual HashKey hash()
            {
                HashKey h;
                h.m_type = type();
                h.m_value = m_value;
                return h;
            }

        public:
            string m_value;
        };
    }
}