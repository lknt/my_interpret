#include <evaluator/evaluator.h>
using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_if(const std::shared_ptr<ast::If> &node, pi::evaluator::Environment *env) {
    for (auto & scenario : node->m_scenarios)
    {
        auto condition = eval(scenario->m_condition, env);
        if (is_error(condition))
        {
            return condition;
        }
        if (is_true(condition))
        {
            auto obj = eval(scenario->m_body, env);
            if (is_error(obj))
            {
                return obj;
            }
            if (obj->type() == Object::OBJECT_BREAK || obj->type() == Object::OBJECT_CONTINUE)
            {
                return obj;
            }
            break;
            //todo: 处理return, break,continue
        }
    }
    return new_null();
}