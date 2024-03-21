#include <object/list.h>
#include <object/integer.h>
#include <object/string.h>
#include <sstream>


using namespace pi::object;

std::map<string, List::method> List::m_methods ={
        {"len",         &List::_len},
        {"append",      &List::_append},
        {"pop",         &List::_pop},
        {"shift",       &List::_shift},
        {"insert",      &List::_insert},
        {"remove",      &List::_remove},
        {"clear",       &List::_clear},
        {"index",       &List::_index},
        {"extend",      &List::_extend},
        {"join",        &List::_join},
        {"json",        &List::_json},
        {"copy",        &List::_copy},
};




string List::str() const
{
    string s;
    s += "[";
    for (int i = 0; i < m_elements.size(); i ++)
    {
        if (i > 0)
        {
            s += ", ";
        }
        auto obj = m_elements[i];
        if (obj->type() == Object::OBJECT_STRING)
        {
            s += "\"" + obj->str() + "\"";
        }
        else
        {
            s += obj->str();
        }
    }
    s += "]";
    return s;
}

std::shared_ptr<Object> List::call(const string & method, const std::vector<std::shared_ptr<Object>> & args)
{
    auto it = m_methods.find(method);
    if (it == m_methods.end())
    {
        return new_error("list not support method: %s", method.c_str());
    }
    return (this->*(it->second))(args);
}


std::shared_ptr<Object> List::_len(const std::vector<std::shared_ptr<Object>> & args)
{
    if (args.size() != 0)
    {
        return new_error("wrong number of arguments. `list.len()` got=%d", args.size());
    }
    return new_integer((int64_t )m_elements.size());
}

std::shared_ptr<Object> List::_append(const std::vector<std::shared_ptr<Object>> & args)
{
    for (auto & arg : args)
    {
        m_elements.push_back(arg);
    }
    return new_null();
}

std::shared_ptr<Object> List::_pop(const std::vector<std::shared_ptr<Object>> & args)
{
    if (args.size() != 0)
    {
        return new_error("wrong number of arguments. `list.pop()` got=%d", args.size());
    }
    if (m_elements.empty())
    {
        return new_null();
    }
    auto elem = m_elements.back();
    m_elements.pop_back();
    return elem;
}

std::shared_ptr<Object> List::_shift(const std::vector<std::shared_ptr<Object>> & args)
{
    if (args.size() != 0)
    {
        return new_error("wrong number of arguments. `list.shift()` got=%d", args.size());
    }
    if (m_elements.empty())
    {
        return new_null();
    }
    auto elem = m_elements.front();
    m_elements.erase(m_elements.begin());
    return elem;
}

std::shared_ptr<Object> List::_insert(const std::vector<std::shared_ptr<Object>> & args)
{
    if (args.size() < 2)
    {
        return new_error("wrong number of arguments. `list.insert()` got=%d", args.size());
    }
    if (args[0]->type() != Object::OBJECT_INTEGER)
    {
        return new_error("first argument to `list.insert()` not support, got: %s", args[0]->name().c_str());
    }
    auto arg = std::dynamic_pointer_cast<Integer>(args[0]);
    if (arg->m_value > m_elements.size())
    {
        return new_error("out of range. `list.insert()` got=%d", arg->m_value);
    }
    std::vector<std::shared_ptr<Object>> elems;
    for (int i = 1; i < args.size(); i ++)
    {
        elems.push_back(args[i]);
    }
    m_elements.insert(m_elements.begin() + arg->m_value, elems.begin(), elems.end());
    return new_null();
}


std::shared_ptr<Object> List::_remove(const std::vector<std::shared_ptr<Object>> & args)
{
    if (args.size() != 1)
    {
        return new_error("wrong number of arguments. `list.remove()` got %d", args.size());
    }
    if (args[0]->type() != Object::OBJECT_INTEGER)
    {
        return new_error("argument to `list.remove()` not supported, got %s", args[0]->name().c_str());
    }
    auto arg = std::dynamic_pointer_cast<Integer>(args[0]);
    if (arg->m_value >= m_elements.size())
    {
        return new_error("out of range. list.remove() got=%d", arg->m_value);
    }
    m_elements.erase(m_elements.begin() + arg->m_value);
    return new_null();
}

std::shared_ptr<Object> List::_clear(const std::vector<std::shared_ptr<Object>> & args)
{
    if (args.size() != 0)
    {
        return new_error("wrong number of arguments. `list.clear()` got %d", args.size());
    }
    m_elements.clear();
    return new_null();
}

std::shared_ptr<Object> List::_index(const std::vector<std::shared_ptr<Object>> & args)
{
    if (args.size() != 1)
    {
        return new_error("wrong number of arguments. `list.index()` got %d", args.size());
    }
    auto arg = args[0];
    for (int i = 0; i < m_elements.size(); i++)
    {
        if ((m_elements[i]->type() == arg->type()) && (m_elements[i]->str() == arg->str()))
        {
            return new_integer(i);
        }
    }
    return new_integer(-1);
}

std::shared_ptr<Object> List::_extend(const std::vector<std::shared_ptr<Object>> & args)
{
    if (args.size() != 1)
    {
        return new_error("wrong number of arguments. `list.extend()` got=%d", args.size());
    }
    if (args[0]->type() != Object::OBJECT_LIST)
    {
        return new_error("argument to `list.extend()` not supported, got %s", args[0]->name().c_str());
    }
    auto list = std::dynamic_pointer_cast<List>(args[0]);
    for (auto & elem : list->m_elements)
    {
        m_elements.push_back(elem);
    }
    return new_null();
}

std::shared_ptr<Object> List::_join(const std::vector<std::shared_ptr<Object>> & args)
{
    if (args.size() != 1)
    {
        return new_error("wrong number of arguments. `list.join()` got %d", args.size());
    }
    if (args[0]->type() != Object::OBJECT_STRING)
    {
        return new_error("argument to `list.join()` not supported, got %s", args[0]->name().c_str());
    }
    auto arg = std::dynamic_pointer_cast<String>(args[0]);
    std::ostringstream oss;
    for (auto it = m_elements.begin(); it != m_elements.end(); it++)
    {
        if (it != m_elements.begin())
        {
            oss << arg->m_value;
        }
        oss << (*it)->str();
    }
    return new_string(oss.str());
}

std::shared_ptr<Object> List::_json(const std::vector<std::shared_ptr<Object>> & args)
{
    if (args.size() != 0)
    {
        return new_error("wrong number of arguments. `list.json()` got %d", args.size());
    }
    return new_string(str());
}


std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>> List::next()
{
    if (m_offset < m_elements.size())
    {
        std::shared_ptr<Integer> first(new Integer(m_offset));
        auto second = m_elements[m_offset];
        m_offset ++;
        std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>> pair(first, second);
        return pair;
    }
    return std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>> (nullptr, nullptr);
}
void List::reset()
{
    m_offset = 0;
}
std::shared_ptr<Object> List::copy()
{
    std::shared_ptr<List> list(new List());
    for (auto & elem : m_elements)
    {
        auto copyable = std::dynamic_pointer_cast<Copyable>(elem);
        if (!copyable)
        {
            return new_error("object not support copyable: %s", elem->name().c_str());
        }
        list->m_elements.push_back(copyable->copy());
    }
    return list;
}

std::shared_ptr<Object> List::_copy(const std::vector<std::shared_ptr<Object>> & args)
{
    if (args.size() != 0)
    {
        return new_error("wrong number of arguments. `list.copy()` got %d", args.size());
    }
    return copy();
}
