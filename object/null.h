#pragma once

#include <object/object.h>
#include <object/hashable.h>

namespace pi
{
    namespace object
    {
        class Null : public Object, public Hashable
        {
        public:
            Null() : Object(OBJECT_NULL) {}
           ~Null() {}
            virtual string str() const
            {
                return "null";
            }
            virtual HashKey hash()
            {
                std::hash<string> hash_func;
                auto hash_code = hash_func("null");

                HashKey h;
                h.m_type = type();
                h.m_value = hash_code;
                return h;
            }
        };
    }
}