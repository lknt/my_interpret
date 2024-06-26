#pragma once

#include <object/object.h>
#include <object/hashable.h>
#include <object/copyable.h>


namespace pi
{
    namespace object
    {
        class Float : public Object, public Hashable, public Copyable
        {
        public:
            Float() : Object(OBJECT_FLOAT), m_value(0) {}
            Float(double value) : Object(OBJECT_FLOAT), m_value(value) {}
            ~Float() {}
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
                return new_float(m_value);
            }

        public:
            double m_value;
        };
    }
}