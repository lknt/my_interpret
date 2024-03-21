
#include <object/string.h>
using namespace pi::object;
#include <object/list.h>
#include <object/integer.h>

std::map<string, String::method> String::m_methods ={
        {"len", &String::_len},
        {"upper", &String::_upper},
        {"lower", &String::_lower},
        {"split", &String::_split},
        {"find", &String::_find},
        {"index", &String::_index},
        {"prefix", &String::_prefix},
        {"suffix", &String::_suffix},
        {"trim", &String::_trim},
        {"repeat", &String::_repeat},
        {"replace", &String::_replace},
};

std::shared_ptr<Object> String::call(const string & method, const std::vector<std::shared_ptr<Object>> & args)
{
    auto it = m_methods.find(method);
    if (it == m_methods.end())
    {
        return new_error("string not support method: %s", method.c_str());
    }
    return (this->*(it->second))(args);
}


std::shared_ptr<Object> String::_len(const std::vector<std::shared_ptr<Object>> & args)
{
    if (args.size() != 0)
    {
        return new_error("wrong number of arguments. `string.len()` got=%d", args.size());
    }
    return new_integer(m_value.size());

}
std::shared_ptr<Object> String::_upper(const std::vector<std::shared_ptr<Object>> & args)
{
    if (args.size() != 0)
    {
        return new_error("wrong number of arguments. `string.upper()` got=%d", args.size());
    }
    string str = m_value;
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return new_string(str);

}
std::shared_ptr<Object> String::_lower(const std::vector<std::shared_ptr<Object>> & args)
{
    if (args.size() != 0)
    {
        return new_error("wrong number of arguments. `string.lower()` got=%d", args.size());
    }
    string str = m_value;
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return new_string(str);
}

std::shared_ptr<Object> String::_split(const std::vector<std::shared_ptr<Object>> &args) {
    if (args.size() != 1)
    {
        return new_error("wrong number of arguments. `string.split()` got=%d", args.size());
    }
    if (args[0]->type() != Object::OBJECT_STRING)
    {
        return new_error("argument to `string.split()` error: %s", args[0]->name().c_str());
    }
    auto arg = std::dynamic_pointer_cast<String>(args[0]);
    auto sep = arg->m_value;
    string input = m_value;
    std::vector<string> output;
    size_t last = 0;
    size_t index = input.find_first_of(sep, last);
    while (index != std::string::npos)
    {
        string str = input.substr(last, index - last);
        output.push_back(str);
        last = index + 1;
        index = input.find_first_of(sep, last);
    }
    if (index - last > 0)
    {
        output.push_back(input.substr(last, index - last));
    }
    std::shared_ptr<List> list(new List());
    for (auto & elem : output)
    {
        std::shared_ptr<String> s(new String(elem));
        list->m_elements.push_back(new_string(elem));
    }
    return list;
}

std::shared_ptr<Object> String::_find(const std::vector<std::shared_ptr<Object>> & args)
{
    if (args.size() != 1)
    {
        return new_error("wrong number of arguments. `string.find()` got=%d", args.size());
    }
    if (args[0]->type() != Object::OBJECT_STRING)
    {
        return new_error("argument to `string.find()` error: %s", args[0]->name().c_str());
    }
    auto arg = std::dynamic_pointer_cast<String>(args[0]);
    if (m_value.find(arg->m_value) != std::string::npos)
    {
        return new_bool(true);
    }
    return new_bool(false);
}

std::shared_ptr<Object> String::_index(const std::vector<std::shared_ptr<Object>> & args)
{
    if (args.size() != 1)
    {
        return new_error("wrong number of arguments. `string.index()` got=%d", args.size());
    }
    if (args[0]->type() != Object::OBJECT_STRING)
    {
        return new_error("argument to `string.index()` error: %s", args[0]->name().c_str());
    }
    auto arg = std::dynamic_pointer_cast<String>(args[0]);
    auto idx = m_value.find(arg->m_value);
    if (idx != std::string::npos)
    {
        return new_integer((int64_t)idx);
    }
    return new_integer(-1);
}

std::shared_ptr<Object> String::_prefix(const std::vector<std::shared_ptr<Object>> & args)
{
    if (args.size() != 1)
    {
        return new_error("wrong number of arguments. `string.prefix()` got=%d", args.size());
    }
    if (args[0]->type() != Object::OBJECT_STRING)
    {
        return new_error("argument to `string.prefix()` error: %s", args[0]->name().c_str());
    }
    auto arg = std::dynamic_pointer_cast<String>(args[0]);
    if (m_value.size() < arg->m_value.size())
    {
        return new_bool(false);
    }
    if (m_value.substr(0, arg->m_value.size()) == arg->m_value)
    {
        return new_bool(true);
    }
    return new_bool(false);
}

std::shared_ptr<Object> String::_suffix(const std::vector<std::shared_ptr<Object>> & args)
{
    if (args.size() != 1)
    {
        return new_error("wrong number of arguments. `string.suffix()` got=%d", args.size());
    }
    if (args[0]->type() != Object::OBJECT_STRING)
    {
        return new_error("argument to `string.suffix()` error: %s", args[0]->name().c_str());
    }
    auto arg = std::dynamic_pointer_cast<String>(args[0]);
    if (m_value.size() < arg->m_value.size())
    {
        return new_bool(false);
    }
    if (m_value.substr(m_value.size() - arg->m_value.size(), arg->m_value.size()) == arg->m_value)
    {
        return new_bool(true);
    }
    return new_bool(false);
}

std::shared_ptr<Object> String::_trim(const std::vector<std::shared_ptr<Object>> & args)
{
    if (args.size() != 1)
    {
        return new_error("wrong number of arguments. `string.trim()` got=%d", args.size());
    }
    if (args[0]->type() != Object::OBJECT_STRING)
    {
        return new_error("argument to `string.trim()` error: %s", args[0]->name().c_str());
    }
    auto arg = std::dynamic_pointer_cast<String>(args[0]);
    string str = m_value;
    //裁剪头部字符
    auto found = str.find_first_not_of(arg->m_value);
    if (found != std::string::npos)
    {
        str.erase(0, found);
    }
    else
    {
        str.clear();
    }
    if (str.empty())
    {
        return new_string(str);
    }

    //裁剪尾部
    found = str.find_last_not_of(arg->m_value);
    if (found != std::string::npos)
    {
        str.erase(found + 1);
    }
    else
    {
        str.clear();
    }
    return new_string(str);
}

std::shared_ptr<Object> String::_repeat(const std::vector<std::shared_ptr<Object>> &args)
{
    if (args.size() != 1)
    {
        return new_error("wrong number of arguments. `string.repeat()` got=%d", args.size());
    }
    if (args[0]->type() != Object::OBJECT_INTEGER)
    {
        return new_error("argument to `string.repeat()` error: %s", args[0]->name().c_str());
    }
    auto arg = std::dynamic_pointer_cast<Integer>(args[0]);
    string str;
    for (auto i = 0; i < arg->m_value; i ++)
    {
        str += m_value;
    }

    return new_string(str);
}

std::shared_ptr<Object> String::_replace(const std::vector<std::shared_ptr<Object>> &args)
{
    if (args.size() != 2)
    {
        return new_error("wrong number of arguments. `string.replace()` got=%d", args.size());
    }
    if (args[0]->type() != Object::OBJECT_STRING )
    {
        return new_error("first argument to `string.replace()` error: %s", args[0]->name().c_str());
    }
    if (args[1]->type() != Object::OBJECT_STRING )
    {
        return new_error("second argument to `string.replace()` error: %s", args[1]->name().c_str());
    }
    auto old_str = std::dynamic_pointer_cast<String>(args[0]);
    auto new_str = std::dynamic_pointer_cast<String>(args[1]);
    string str = m_value;
    while(true)
    {
        auto pos = str.find(old_str->m_value);
        if (pos != std::string::npos)
        {
            str.replace(pos, old_str->m_value.length(), new_str->m_value);
        }
        else
        {
            break;
        }
    }
    return new_string(str);
}