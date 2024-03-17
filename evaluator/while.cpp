#include <evaluator/evaluator.h>
using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_while(const std::shared_ptr<ast::While> &node,
                                              pi::evaluator::Environment *env) {
    auto condition = eval(node->m_condition, env);
    if (is_error(condition))
    {
        return condition;
    }
    while (is_true(condition))
    {
        auto obj = eval(node->m_body, env);
        if (is_error(obj)) {
            return obj;
        }
        if (obj->type() == Object::OBJECT_BREAK)
        {
            break;
        }
        else if (obj->type() == Object::OBJECT_RETURN)
        {
            return obj;
        }
        condition = eval(node->m_condition, env);
        if (is_error(condition)){
            return condition;
        }
    }
    return new_null();
}