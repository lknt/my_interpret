#include <evaluator/evaluator.h>
using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_list(const std::shared_ptr<ast::List> &node, pi::evaluator::Environment *env) {
    std::shared_ptr<object::List> l(new object::List());
    for (auto & exp : node->m_elements)
    {
        auto obj = eval(exp, env);
        if (is_error(obj))
        {
            return obj;
        }
        l->m_elements.push_back(obj);
    }
    return l;
}