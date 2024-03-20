#include <evaluator/evaluator.h>
using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_method(const std::shared_ptr<ast::Method> & node, Environment * env)
{
    auto obj = eval(node->m_object, env);
    if (is_error(obj))
    {
        return obj;
    }
    std::vector<std::shared_ptr<Object>> args;
    for (int i = 0; i < node->m_arguments.size(); i ++)
    {
        auto arg = eval(node->m_arguments[i], env);
        if (is_error(arg))
        {
            return arg;
        }
        args.push_back(arg);
    }
    return apply_method(obj, node->m_method, args);
}
std::shared_ptr<Object> Evaluator::apply_method(const std::shared_ptr<Object> & obj, const std::shared_ptr<ast::Expression> & method, const std::vector<std::shared_ptr<Object>> & args) {
    if (method->type() != Node::NODE_IDENTIFIER)
    {
        return new_error("method is not identifier");
    }
    auto m = std::dynamic_pointer_cast<ast::Identifier>(method);
    switch (obj->type()) {
        case Object::OBJECT_STRING:
        {
            return new_string("string method");
        }
        case Object::OBJECT_LIST:
        {
            return new_string("list method");
        }
        case Object::OBJECT_HASH:
        {
            return new_string("hash method");
        }
        default:
            break;
    }
    return new_error("%s does not have method '%s()'", obj->name().c_str(), m->m_value.c_str());
}
