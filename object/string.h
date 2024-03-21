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

            typedef std::shared_ptr<Object> (String::*method)(const std::vector<std::shared_ptr<Object>> &);
            std::shared_ptr<Object> call(const string & method, const std::vector<std::shared_ptr<Object>> & args);

        private:
            std::shared_ptr<Object> _len(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _upper(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _lower(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _split(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _find(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _index(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _prefix(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _suffix(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _trim(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _repeat(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _replace(const std::vector<std::shared_ptr<Object>> & args);
        public:
            string m_value;
            static std::map<string, method> m_methods;
        };
    }
}