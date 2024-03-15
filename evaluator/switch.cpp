#include <evaluator/evaluator.h>
using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_switch(const std::shared_ptr<ast::Switch> &node,
                                               pi::evaluator::Environment *env) {
    auto obj = eval(node->m_value, env);
    if (is_error(obj))
    {
        return obj;
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
            if (obj->type() == res->type() && obj->str() == res->str())
            {
                eval_block(opt->m_body, env);
                return new_null();
            }
        }
    }
    for (auto & opt : node->m_cases)
    {
        if (opt->m_default)
        {
            eval_block(opt->m_body, env);
            return new_null();
        }
    }
    return new_null();
}