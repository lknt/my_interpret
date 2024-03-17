#include <evaluator/evaluator.h>
using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_switch(const std::shared_ptr<ast::Switch> &node,
                                               pi::evaluator::Environment *env) {
    auto val = eval(node->m_value, env);
    if (is_error(val))
    {
        return val;
    }
    for (auto & opt : node->m_cases)
    {
        if (opt->m_default)
        {
            continue;
        }
        for (auto & exp : opt->m_values)
        {
            auto res = eval(exp, env);
            if (val->type() == res->type() && val->str() == res->str())
            {
                auto obj = eval_block(opt->m_body, env);
                if (is_error(obj))
                {
                    return obj;
                }
                if (obj->type() == Object::OBJECT_RETURN)
                {
                    return obj;
                }
                return new_null();
            }
        }
    }
    for (auto & opt : node->m_cases)
    {
        if (opt->m_default)
        {
            auto obj = eval_block(opt->m_body, env);
            if (is_error(obj))
            {
                return obj;
            }
            if (obj->type() == Object::OBJECT_RETURN)
            {
                return obj;
            }
            break;
        }
    }
    return new_null();
}