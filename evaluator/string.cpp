#include <evaluator/evaluator.h>

using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_string(const std::shared_ptr<ast::String> &node)
{
    return new_string(node->m_value);
}
