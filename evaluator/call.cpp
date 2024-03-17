#include <evaluator/evaluator.h>
using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_call(const std::shared_ptr<ast::Call> &node, pi::evaluator::Environment *env) {
    auto obj = eval(node->m_function, env);
    if (is_error(obj))
    {
        return obj;
    }
    std::vector<std::shared_ptr<Object>>args;
    switch (obj->type()) {
        case Object::OBJECT_FUNCTION:
        {
            auto fn = std::dynamic_pointer_cast<object::Function>(obj);
            for (int i = 0; i < node->m_arguments.size(); i ++)
            {
                auto arg = eval(node->m_arguments[i], env);
                if (is_error(arg))
                {
                    return arg;
                }
                args.push_back(arg);
            }
            break;
        }
        default:
        {
            return new_error("not a callable object : %s", obj->name().c_str());
        }
    }
    return apply_function(obj, args);
}

std::shared_ptr<Object> Evaluator::apply_function(const std::shared_ptr<Object> & fn, const std::vector<std::shared_ptr<Object>> &args)
{
    switch (fn->type()) {
        case Object::OBJECT_FUNCTION:
        {
            auto func = std::dynamic_pointer_cast<object::Function>(fn);
            auto ext_env = extend_function_env(func, args);
            if (!ext_env){
                return new_error("extend function environment");
            }
            auto obj = eval(func->m_body, ext_env);
            if (obj->type() == Object::OBJECT_RETURN)
            {
                auto ret = std::dynamic_pointer_cast<object::Return>(obj);
                return ret->m_value;
            }
            return obj;
        }
        default:
        {
            return new_error("not a function: %s", fn->name().c_str());
        }
    }
}

Environment * Evaluator::extend_function_env(const std::shared_ptr<object::Function> &fn,
                                    const std::vector<std::shared_ptr<Object>> &args) {
    if (fn->m_parameters.size() != args.size())
    {
//        printf("%d %d\n", fn->m_parameters.size(), args.size());
        return nullptr;
    }
    Environment * env = new Environment(fn->m_env);
    for (int i = 0; i < fn->m_parameters.size(); i ++)
    {
        env->set(fn->m_parameters[i]->m_value, args[i]);
    }
    return env;
}