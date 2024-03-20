#include <object/builtin.h>
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
    return new_null();
}
std::shared_ptr<Object> Builtin::_int(const std::vector<std::shared_ptr<Object>> & args){
    return new_null();
}
std::shared_ptr<Object> Builtin::_float(const std::vector<std::shared_ptr<Object>> & args){
    return new_null();
}
std::shared_ptr<Object> Builtin::_str(const std::vector<std::shared_ptr<Object>> & args){
    return new_null();
}
std::shared_ptr<Object> Builtin::_exit(const std::vector<std::shared_ptr<Object>> & args){
    return new_null();
}
