#include <evaluator/evaluator.h>
using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_block(const std::shared_ptr<ast::Block> &node,
                                              pi::evaluator::Environment *env) {
    std::shared_ptr<Object> result;
    for (auto & stat : node->m_statements)
    {
        auto obj = eval(stat, env);
        if (is_error(obj))
        {
            return obj;
        }
        Object::Type type = obj->type();
        if (type == Object::OBJECT_BREAK || type == Object::OBJECT_CONTINUE)
        {
            return obj;
        }


        // todo: 处理return
    }
    return new_null();
}