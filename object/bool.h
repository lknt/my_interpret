#pragma once

#include <object/object.h>

namespace pi {
    namespace object {
        class Bool : public Object
        {
        public:
            Bool() : Object(OBJECT_BOOL), m_value(false) {}
            Bool(bool value) : Object(OBJECT_BOOL), m_value(value) {}
            ~Bool() {}

            virtual string str()
            {
                return m_value ? "true" : "false";
            }

        public:
            bool m_value;
        };
    }
}