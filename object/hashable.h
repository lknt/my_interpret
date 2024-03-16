#pragma once

#include <object/object.h>

namespace pi {
    namespace object {
        class HashKey
        {
        public:
            HashKey() {}
            ~HashKey() {}

            bool operator < (const HashKey & key) const
            {
                return m_value < key.m_value;
            }
            bool operator <= (const HashKey & key) const
            {
                return m_value <= key.m_value;
            }
            bool operator > (const HashKey & key) const
            {
                return m_value > key.m_value;
            }
            bool operator >= (const HashKey & key) const
            {
                return m_value >= key.m_value;
            }
            bool operator == (const HashKey & key) const
            {
                return m_value == key.m_value;
            }
            bool operator != (const HashKey & key) const
            {
                return m_value != key.m_value;
            }
        public:
            Object::Type m_type;
            uint64_t m_value;
        };

        class Hashable
        {
        public:
            virtual HashKey hash() = 0;
        };
    }

}