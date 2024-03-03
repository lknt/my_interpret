#pragma once

#include <object/object.h>

namespace pi
{
    namespace object
    {
        class String : public Object
        {
        public:
            String() : Object(OBJECT_STRING) {}
            String(string & value) : Object(OBJECT_STRING), m_value(value) {}
            ~String() {}
            virtual string str()
            {
                return m_value;
            }

        public:
            string m_value;
        };
    }
}