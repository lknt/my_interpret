#include <evaluator/evaluator.h>
using namespace pi::evaluator;

std::shared_ptr<Object>Evaluator::eval_ternary(const std::shared_ptr<ast::Ternary> &node, pi::evaluator::Environment *env) {
    auto condition = eval(node->m_condition, env);
    if (is_error(condition))
    {
        return condition;
    }
    if (is_true(condition))
    {
        return eval(node->m_if_true, env);
    }
    return eval(node->m_if_false, env);
}