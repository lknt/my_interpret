#include <evaluator/evaluator.h>
using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_compound(const std::shared_ptr<ast::Compound> &node,
                                                 pi::evaluator::Environment *env) {
    auto left = eval(node->m_left, env);
    if (is_error(left))
    {
        return left;
    }
    auto right = eval(node->m_right, env);
    if (is_error(right))
    {
        return right;
    }
    string op = node->m_operator.substr(0, node->m_operator.size() - 1);

    auto val = eval_infix(op, left, right, env);
    if (is_error(val))
    {
        return val;
    }
    switch (node->m_left->type()) {
        case Node::NODE_IDENTIFIER:
        {
            auto expr = std::dynamic_pointer_cast<ast::Identifier>(node->m_left);
            env->set(expr->m_value, val);
            return new_null();
        }
        default:
        {
            return new_null();
        }
    }
}