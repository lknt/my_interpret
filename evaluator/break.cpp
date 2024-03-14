#include <evaluator/evaluator.h>
using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_break(const std::shared_ptr<ast::Break> &node) {
    return new_break();
}