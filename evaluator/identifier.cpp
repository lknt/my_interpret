#include <evaluator/evaluator.h>
using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_identifier(const std::shared_ptr<ast::Identifier> &node) {
    return new_error("identifier not found %s", node->m_value.c_str());
}