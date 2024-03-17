#include <evaluator/evaluator.h>
using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_function(const std::shared_ptr<ast::Function> &node,
                                                 pi::evaluator::Environment *env) {
    std::shared_ptr<object::Function> fn(new object::Function());
    fn->m_parameters = node->m_parameters;
    fn->m_defaults = node->m_defaults;
    fn->m_body = node->m_body;
    fn->m_env = env;
    return fn;
}