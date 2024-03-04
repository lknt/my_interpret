#include <evaluator/evaluator.h>
using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_identifier(const std::shared_ptr<ast::Identifier> &node,
                                                   pi::evaluator::Environment *env) {
    auto obj = env->get(node->m_value);
    if (obj)
    {
        return obj;
    }
    return new_error("identifier not found %s", node->m_value.c_str());
}