#include <object/hash.h>
#include <object/list.h>
using namespace pi::object;

std::map<string, Hash::method> Hash::m_methods = {
        {"len",         &Hash::_len},
        {"has",         &Hash::_has},
        {"get",         &Hash::_get},
        {"set",         &Hash::_set},
        {"keys",         &Hash::_keys},
        {"values",         &Hash::_values},
        {"update",         &Hash::_update},
        {"remove",         &Hash::_remove},
        {"clear",         &Hash::_clear},
        {"json",         &Hash::_json},
};


string Hash::str() const
{
    string s;
    s += "{";
    for (auto it = m_pairs.begin(); it != m_pairs.end(); it ++)
    {
        if (it != m_pairs.begin())
        {
            s += ", ";
        }
        auto key = it->second.m_key;
        auto val = it->second.m_value;
        if (key->type() == OBJECT_STRING)
        {
            s += "\""+ key->str() + "\"";
        }
        else
        {
            s += key->str();
        }
        s += ": ";
        if (val->type() == OBJECT_STRING)
        {
            s += "\""+ val->str() + "\"";
        }
        else
        {
            s += val->str();
        }
    }
    s += "}";
    return s;
}

std::shared_ptr<Object> Hash::call(const string & method, const std::vector<std::shared_ptr<Object>> & args)
{
    auto it = m_methods.find(method);
    if (it == m_methods.end())
    {
        return new_error("string not support method: %s", method.c_str());
    }
    return (this->*(it->second))(args);
}

std::shared_ptr<Object> Hash::_len(const std::vector<std::shared_ptr<Object>> &args) {
    if (args.size() != 0)
    {
        return new_error("wrong number of `hash.len()` expect got:%d", args.size());
    }
    return new_integer((int64_t)m_pairs.size());
}

std::shared_ptr<Object> Hash::_has(const std::vector<std::shared_ptr<Object>> &args) {
    if (args.size() != 1)
    {
        return new_error("wrong number of `hash.len()` expect got:%d", args.size());
    }
    auto arg = std::dynamic_pointer_cast<Hashable>(args[0]);
    if (!arg)
    {
        return new_error("argument not support hashable interface: %s", args[0]->name().c_str());
    }
    HashKey key = arg->hash();
    if (m_pairs.find(key) != m_pairs.end())
    {
        return new_bool(true);
    }
    else
    {
        return new_bool(false);
    }
}

std::shared_ptr<Object> Hash::_get(const std::vector<std::shared_ptr<Object>> &args) {
    if (args.size() < 1 || args.size() > 2)
    {
        return new_error("wrong number of `hash.get()` expect got:%d", args.size());
    }
    auto arg = std::dynamic_pointer_cast<Hashable>(args[0]);
    if (!arg)
    {
        return new_error("argument not support hashable interface : %s", args[0]->name().c_str());
    }
    HashKey key = arg->hash();
    auto it = m_pairs.find(key);
    if (it != m_pairs.end())
    {
        return it->second.m_value;
    }
    if (args.size() == 2)
    {
        return args[1];
    }
    return new_null();
}

std::shared_ptr<Object> Hash::_set(const std::vector<std::shared_ptr<Object>> &args) {
    if (args.size() != 2)
    {
        return new_error("wrong number of `hash.set()` expect got:%d", args.size());
    }
    auto arg = std::dynamic_pointer_cast<Hashable>(args[0]);
    if (!arg)
    {
        return new_error("argument not support hashable interface: %s", args[0]->name().c_str());
    }
    HashKey key = arg->hash();
    HashPair pair;
    pair.m_key = args[0];
    pair.m_value = args[1];
    m_pairs[key] = pair;
    return new_null();
}

std::shared_ptr<Object> Hash::_keys(const std::vector<std::shared_ptr<Object>> & args)
{
    if (args.size() != 0)
    {
        return new_error("wrong number of `hash.keys()` expect got:%d", args.size());
    }
    std::shared_ptr<List> list(new List());
    for (auto & pair : m_pairs)
    {
        list->m_elements.push_back(pair.second.m_key);
    }
    return list;
}
std::shared_ptr<Object> Hash::_values(const std::vector<std::shared_ptr<Object>> & args)
{
    if (args.size() != 0)
    {
        return new_error("wrong number of `hash.values()` expect got:%d", args.size());
    }
    std::shared_ptr<List> list(new List());
    for (auto & pair : m_pairs)
    {
        list->m_elements.push_back(pair.second.m_value);
    }
    return list;
}

std::shared_ptr<Object> Hash::_update(const std::vector<std::shared_ptr<Object>> & args)
{
    if (args.size() != 1)
    {
        return new_error("wrong number of `hash.update()` expect got:%d", args.size());
    }
    auto arg = args[0];
    if (arg->type() != Object::OBJECT_HASH)
    {
        return new_error("argument to `hash.update()` type error, got %s", arg->name().c_str());
    }
    auto hash = std::dynamic_pointer_cast<Hash>(arg);
    for (auto & pair : hash->m_pairs)
    {
        m_pairs[pair.first] = pair.second;
    }

    return new_null();
}

std::shared_ptr<Object> Hash::_remove(const std::vector<std::shared_ptr<Object>> & args)
{
    if (args.size() != 1)
    {
        return new_error("wrong number of `hash.remove()` expect got:%d", args.size());
    }
    auto arg = std::dynamic_pointer_cast<Hashable>(args[0]);
    if (!arg)
    {
        return new_error("argument not support hashable interface: %s", args[0]->name().c_str());
    }
    HashKey key = arg->hash();
    auto it = m_pairs.find(key);
    if (it != m_pairs.end())
    {
        m_pairs.erase(it);
    }

    return new_null();
}

std::shared_ptr<Object> Hash::_clear(const std::vector<std::shared_ptr<Object>> & args)
{
    if (args.size() != 0)
    {
        return new_error("wrong number of `hash.clear()` expect got:%d", args.size());
    }
    m_pairs.clear();

    return new_null();
}

std::shared_ptr<Object> Hash::_json(const std::vector<std::shared_ptr<Object>> & args)
{
    if (args.size() != 0)
    {
        return new_error("wrong number of `hash.json()` expect got:%d", args.size());
    }

    return new_string(str());
}