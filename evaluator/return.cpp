#include <evaluator/evaluator.h>

using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_return(const std::shared_ptr<ast::Return> &node,
                                               pi::evaluator::Environment *env) {
    auto obj = eval(node->m_value, env);
    if (is_error(obj))
    {
        return obj;
    }
    std::shared_ptr<object::Return> ret(new object::Return());
    ret->m_value = obj;
    return ret;
}
