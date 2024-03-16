#pragma once

#include <object/object.h>
#include <object/hashable.h>

namespace pi
{
    namespace object
    {
        class HashPair
        {
        public:
            HashPair() {}
            HashPair(const std::shared_ptr<Object> & key, const std::shared_ptr<Object> & value) : m_key(key), m_value(value) {};
            ~HashPair() {}


        public:
            std::shared_ptr<Object> m_key;
            std::shared_ptr<Object> m_value;
        };

        class Hash : public Object
        {
        public:
            Hash() : Object(OBJECT_HASH) {}
            ~Hash() {}
            virtual string str() const;


        public:
            std::map<HashKey, HashPair> m_pairs;
        };
    }
}