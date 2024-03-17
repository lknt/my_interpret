#include <evaluator/evaluator.h>
using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_for(const std::shared_ptr<ast::For> &node, pi::evaluator::Environment *env) {
    auto starter = eval(node->m_starter, env);
    if (is_error(starter))
    {
        return starter;
    }
    while (true)
    {
        auto condition = eval(node->m_condition, env);
        if (is_error(condition)){
            return condition;
        }
        if (!is_true(condition))
        {
            break;
        }
        auto obj = eval(node->m_body, env);
        if (is_error(obj)) {
            return obj;
        }
        auto type = obj->type();
        if (type == Object::OBJECT_BREAK)
        {
            break;
        }
        else if (type == Object::OBJECT_RETURN)
        {
            return obj;
        }
        else if (type == Object::OBJECT_CONTINUE)
        {
            auto closer = eval(node->m_closer, env);
            if (is_error(closer))
            {
                return closer;
            }
        }
//        else if (type == Object::OBJECT_RETURN)
//        {
//
//        }
        auto closer = eval(node->m_closer, env);
        if (is_error(closer))
        {
            return closer;
        }
    }
    return new_null();
}