#pragma once

#include <object/object.h>
#include <object/iterable.h>
#include <object/copyable.h>


namespace pi
{
    namespace object
    {
        class List : public Object, public Iterable, public Copyable
        {
        public:
            List() : Object(OBJECT_LIST), m_offset(0) {}
            ~List() {}
            virtual string str() const;
            virtual std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>> next();
            virtual void reset();
            virtual std::shared_ptr<Object> copy();

            typedef std::shared_ptr<Object> (List::*method)(const std::vector<std::shared_ptr<Object>> &);
            std::shared_ptr<Object> call(const string & method, const std::vector<std::shared_ptr<Object>> & args);

        private:
            std::shared_ptr<Object> _len(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _append(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _pop(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _shift(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _insert(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _remove(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _clear(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _index(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _extend(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _join(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _json(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _copy(const std::vector<std::shared_ptr<Object>> & args);

        public:
            std::vector<std::shared_ptr<Object>> m_elements;
            static std::map<string, method> m_methods;
            int64_t m_offset;
        };
    }
}