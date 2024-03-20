#include <object/builtin.h>
#include <object/null.h>
#include <object/integer.h>
#include <object/float.h>
#include <object/string.h>
#include <object/bool.h>
#include <object/list.h>
#include <object/hash.h>
using namespace pi::object;

std::map<string, Builtin::method> Builtin::m_methods = {
        {"print", &Builtin::_print},
        {"type", &Builtin::_type},
        {"len", &Builtin::_len},
        {"int", &Builtin::_int},
        {"float", &Builtin::_float},
        {"str", &Builtin::_str},
        {"exit", &Builtin::_exit},
};

std::shared_ptr<Builtin> Builtin::find(const std::string &name) {
    auto it = m_methods.find(name);
    if (it == m_methods.end())
    {
        return nullptr;
    }
    std::shared_ptr<Builtin> builtin(new Builtin());
    builtin->m_name = name;
    return builtin;
}

std::shared_ptr<Object> Builtin::call(const std::vector<std::shared_ptr<Object>> &args) {
    auto func = m_methods[m_name];
    return (this->*func)(args);
}

std::shared_ptr<Object> Builtin::_print(const std::vector<std::shared_ptr<Object>> & args)
{
    for (auto it = args.begin(); it != args.end(); it ++)
    {
        if (it != args.begin())
        {
            std::cout << " ";
        }
        std::cout << (*it)->str();
    }
    std::cout << std::endl;
    return new_null();
}

std::shared_ptr<Object> Builtin::_type(const std::vector<std::shared_ptr<Object>> &args) {
    if (args.size() != 1)
    {
        return new_error("wrong number of arguments. `type()` got=%d", args.size());
    }
    auto arg =args[0];
    return new_string(arg->name());
}

std::shared_ptr<Object> Builtin::_len(const std::vector<std::shared_ptr<Object>> & args){
    if (args.size() != 1)
    {
        return new_error("wrong number of arguments. `type()` got=%d", args.size());
    }
    auto arg =args[0];
    switch (arg->type()) {
        case Object::OBJECT_STRING:
        {
            auto obj = std::dynamic_pointer_cast<String>(arg);
            return new_integer((int64_t)obj->m_value.size());
        }
        case Object::OBJECT_LIST:
        {
            auto obj = std::dynamic_pointer_cast<List>(arg);
            return new_integer((int64_t)obj->m_elements.size());
        }
        case Object::OBJECT_HASH:
        {
            auto obj = std::dynamic_pointer_cast<Hash>(arg);
            return new_integer((int64_t)obj->m_pairs.size());
        }
        default:
            break;
    }
    return new_error("argument to `len` not supported, got: %s", arg->name().c_str());
}
std::shared_ptr<Object> Builtin::_int(const std::vector<std::shared_ptr<Object>> & args){
    if (args.size() != 1)
    {
        return new_error("wrong number of arguments. `type()` got=%d", args.size());
    }
    auto arg =args[0];
    switch (arg->type()) {
        case Object::OBJECT_BOOL:
        {
            auto obj = std::dynamic_pointer_cast<Bool>(arg);
            return new_integer(obj->m_value ? 1 : 0);
        }
        case Object::OBJECT_INTEGER:
        {
            auto obj = std::dynamic_pointer_cast<Integer>(arg);
            return new_integer((int64_t)obj->m_value);
        }
        case Object::OBJECT_FLOAT:
        {
            auto obj = std::dynamic_pointer_cast<Float>(arg);
            return new_integer((int64_t)obj->m_value);
        }
        case Object::OBJECT_STRING:
        {
            auto obj = std::dynamic_pointer_cast<String>(arg);
            return new_integer(std::stoi(obj->m_value));
        }
        default:
            break;
    }
    return new_error("argument to `int` not supported, got: %s", arg->name().c_str());
}
std::shared_ptr<Object> Builtin::_float(const std::vector<std::shared_ptr<Object>> & args){
    if (args.size() != 1)
    {
        return new_error("wrong number of arguments. `type()` got=%d", args.size());
    }
    auto arg =args[0];
    switch (arg->type()) {
        case Object::OBJECT_BOOL:
        {
            auto obj = std::dynamic_pointer_cast<Bool>(arg);
            return new_float(obj->m_value ? 1 : 0);
        }
        case Object::OBJECT_INTEGER:
        {
            auto obj = std::dynamic_pointer_cast<Integer>(arg);
            return new_float((double)obj->m_value);
        }
        case Object::OBJECT_FLOAT:
        {
            auto obj = std::dynamic_pointer_cast<Float>(arg);
            return new_float(obj->m_value);
        }
        case Object::OBJECT_STRING:
        {
            auto obj = std::dynamic_pointer_cast<String>(arg);
            return new_float(std::stod(obj->m_value));
        }
        default:
            break;
    }
    return new_error("argument to `float` not supported, got: %s", arg->name().c_str());
}
std::shared_ptr<Object> Builtin::_str(const std::vector<std::shared_ptr<Object>> & args){
    if (args.size() != 1)
    {
        return new_error("wrong number of arguments. `type()` got=%d", args.size());
    }
    auto arg =args[0];
    switch (arg->type()) {
        case Object::OBJECT_BOOL:
        case Object::OBJECT_INTEGER:
        case Object::OBJECT_FLOAT:
        case Object::OBJECT_STRING:
        case Object::OBJECT_LIST:
        case Object::OBJECT_HASH:
        case Object::OBJECT_NULL:
        {
            return new_string(arg->str());
        }
        default:
            break;
    }
    return new_error("argument to `str` not supported, got: %s", arg->name().c_str());
}
std::shared_ptr<Object> Builtin::_exit(const std::vector<std::shared_ptr<Object>> & args){
    if (args.size() != 1)
    {
        return new_error("wrong number of arguments. `type()` got=%d", args.size());
    }
    auto arg =args[0];
    if (arg->type() != Object::OBJECT_INTEGER)
    {
        return new_error("aurgument to `exit()` not supported, got %s", arg->name().c_str());
    }
    auto obj = std::dynamic_pointer_cast<Integer>(arg);
    ::exit((int)obj->m_value);
}
