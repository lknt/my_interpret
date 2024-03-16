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
                std::hash<string> hash_func;
                auto hash_code = hash_func(m_value);
                HashKey h;
                h.m_type = type();
                h.m_value = hash_code;
                return h;
            }

        public:
            string m_value;
        };
    }
}