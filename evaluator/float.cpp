#include <evaluator/evaluator.h>
using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_float(const std::shared_ptr<ast::Float> &node) {
    return new_float(node->m_values);
}