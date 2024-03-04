#include <evaluator/evaluator.h>

using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_program(const std::list<std::shared_ptr<ast::Statement>> &stmts,
                                                pi::evaluator::Environment *env) {
    std::shared_ptr<Object> result;
    for (auto & stat : stmts)
    {
        result = eval(stat, env);
        if (is_error(result))
        {
            break;
        }
    }
    return result;
}