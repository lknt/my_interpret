#include <evaluator/evaluator.h>

using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_program(const std::list<std::shared_ptr<ast::Statement>> &stmts) {
    std::shared_ptr<Object> result;
    for (auto & stat : stmts)
    {
        result = eval(stat);
        if (is_error(result))
        {
            break;
        }
    }
    return result;
}