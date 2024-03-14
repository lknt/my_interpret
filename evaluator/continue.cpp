#include <evaluator/evaluator.h>
using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_continue(const std::shared_ptr<ast::Continue> &node) {
    return new_continue();
}