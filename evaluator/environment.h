#pragma once
#include <object/object.h>
using namespace pi::object;

namespace pi
{
    namespace evaluator
    {
        class Environment
        {
        public:
            Environment() : m_outer(nullptr){}
            Environment(Environment * outer) : m_outer(outer) {}
            ~Environment(){}

            void set(const string & name, const std::shared_ptr<Object> & value)
            {
                m_store[name] = value;
            }

            std::shared_ptr<Object> get(const string & name)
            {
                auto it = m_store.find(name);
                if (it != m_store.end())
                {
                    return it->second;
                }
                if (m_outer)
                {
                    return m_outer->get(name);
                }
                return nullptr;
            }

            bool has(const string & name)
            {
                auto it = m_store.find(name);
                if (it != m_store.end())
                {
                    return true;
                }
                if (m_outer)
                {
                    return m_outer->has(name);
                }
                return false;
            }

            void remove(const string & name)
            {
                auto it = m_store.find(name);
                if (it != m_store.end())
                {
                    m_store.erase(it);
                }
            }

            void clear()
            {
                m_store.clear();
            }
        private:
            std::map<string, std::shared_ptr<Object>> m_store;
            std::shared_ptr<Environment> m_outer;
        };
    }
}