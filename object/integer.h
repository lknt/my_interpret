#pragma once

#include <object/object.h>
#include <object/hashable.h>
#include <object/copyable.h>


namespace pi
{
    namespace object
    {
        class Integer : public Object, public Hashable, public Copyable
        {
        public:
            Integer() : Object(OBJECT_INTEGER), m_value(0) {}
            Integer(int64_t value) : Object(OBJECT_INTEGER), m_value(value) {}
            ~Integer() {}
            virtual string str() const
            {
                return std::to_string(m_value);
            }
            virtual HashKey hash()
            {
                std::hash<string> hash_func;
                auto hash_code = hash_func(std::to_string(m_value));

                HashKey h;
                h.m_type = type();
                h.m_value = hash_code;
                return h;
            }
            virtual std::shared_ptr<Object> copy()
            {
                return new_integer(m_value);
            }
        public:
            int64_t m_value;
        };
    }
}