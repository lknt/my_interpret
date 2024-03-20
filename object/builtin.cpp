#include <object/builtin.h>
using namespace pi::object;

std::map<string, Builtin::method> Builtin::m_methods = {
        {"print", &Builtin::_print},
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