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

        // todo: 处理return
        switch (obj->type()) {
            case Object::OBJECT_BREAK:
            case Object::OBJECT_CONTINUE:
            case Object::OBJECT_RETURN:
            {
                return obj;
            }
            default:
                break;
        }

    }
    return new_null();
}