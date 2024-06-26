#pragma once

#include <object/object.h>
#include <object/hashable.h>
#include <object/copyable.h>


namespace pi {
    namespace object {
        class Bool : public Object, public Hashable, public Copyable
        {
        public:
            Bool() : Object(OBJECT_BOOL), m_value(false) {}
            Bool(bool value) : Object(OBJECT_BOOL), m_value(value) {}
            ~Bool() {}

            virtual string str() const
            {
                return m_value ? "true" : "false";
            }
            virtual HashKey hash()
            {
                std::hash<string> hash_func;
                auto hash_code = hash_func(m_value ? "true" : "false");

                HashKey h;
                h.m_type = type();
                h.m_value = hash_code;
                return h;
            }
            virtual std::shared_ptr<Object> copy()
            {
                return new_bool(m_value);
            }

        public:
            bool m_value;
        };
    }
}