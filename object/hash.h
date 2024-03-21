#pragma once

#include <object/object.h>
#include <object/hashable.h>
#include <object/iterable.h>
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
            Hash() : Object(OBJECT_HASH), m_offset(0) {}
            ~Hash() {}
            virtual string str() const;
            virtual std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>> next();
            virtual void reset();

            typedef std::shared_ptr<Object> (Hash::*method)(const std::vector<std::shared_ptr<Object>> &);
            std::shared_ptr<Object> call(const string & method, const std::vector<std::shared_ptr<Object>> & args);

        private:
            std::shared_ptr<Object> _len(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _has(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _get(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _set(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _keys(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _values(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _update(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _remove(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _clear(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _json(const std::vector<std::shared_ptr<Object>> & args);

        public:
            std::map<HashKey, HashPair> m_pairs;
            static std::map<string, method> m_methods;
            int m_offset;
        };
    }
}