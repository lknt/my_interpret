#include <evaluator/evaluator.h>
using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_bool(const std::shared_ptr<ast::Bool> &node) {
    return new_bool(node->m_value);
}