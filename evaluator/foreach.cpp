#include <evaluator/evaluator.h>
using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_foreach(const std::shared_ptr<ast::Foreach> &node,
                                                pi::evaluator::Environment *env) {
    auto obj = eval(node->m_iterable, env);
    auto iterable = std::dynamic_pointer_cast<object::Iterable>(obj);
    if (!iterable)
    {
        return new_error("object %s is not an iterable, can not be used in for loop", obj->name().c_str());
    }
    auto pair = iterable->next();
    while (pair.first)
    {
        env->set(node->m_key, pair.first);
        env->set(node->m_value, pair.second);
        auto res = eval(node->m_body, env);
        if (is_error(res))
        {
            iterable->reset();
            return res;
        }
        if (res->type() == Object::OBJECT_BREAK)
        {
            break;
        }
//        else if (res->type() == Object::OBJECT_CONTINUE)
//        {
//            iterable->next();
//            continue;
//        }
        else if (res->type() == Object::OBJECT_RETURN)
        {
            iterable->reset();
            return res;
        }
        pair = iterable->next();
    }
    iterable->reset();
    return new_null();
}