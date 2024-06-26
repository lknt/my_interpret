#include <evaluator/evaluator.h>

using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_prefix(const std::shared_ptr<ast::Prefix> &node,
                                               pi::evaluator::Environment *env) {
    string op = node->m_operator;
    auto right = eval(node->m_right, env);
    if (is_error(right))
    {
        return right;
    }
    if (op == "-")
    {
        return eval_minus_prefix_operator_expression(right);
    }
    else if (op == "~")
    {
        return eval_tilde_prefix_operator_expression(right);
    }
    else if (op == "!")
    {
        return eval_bang_prefix_operator_expression(right);
    }
    return new_error("unknown operator :%s %s", op.c_str(), right->name().c_str());
}

std::shared_ptr<Object> Evaluator::eval_minus_prefix_operator_expression(std::shared_ptr<Object> &right) {
    switch (right->type()) {
        case Object::OBJECT_INTEGER:
        {
            auto r = std::dynamic_pointer_cast<object::Integer>(right);
            return new_integer(-(r->m_value));
        }
        default:
        {
            return new_error("unknown operator: -%s", right->name().c_str());
        }
    }
}

std::shared_ptr<Object> Evaluator::eval_tilde_prefix_operator_expression(std::shared_ptr<Object> &right) {
    switch (right->type()) {
        case Object::OBJECT_INTEGER:
        {
            auto r = std::dynamic_pointer_cast<object::Integer>(right);
            return new_integer(~(r->m_value));
        }
        default:
        {
            return new_error("unknown operator: ~%s", right->name().c_str());
        }
    }
}

std::shared_ptr<Object> Evaluator::eval_bang_prefix_operator_expression(std::shared_ptr<Object> &right) {
    switch (right->type()) {
        case Object::OBJECT_BOOL:
        {
            auto r = std::dynamic_pointer_cast<object::Bool>(right);
            return new_bool(!(r->m_value));
        }
        case Object::OBJECT_INTEGER:
        {
            auto r = std::dynamic_pointer_cast<object::Integer>(right);
            return new_bool(!(r->m_value));
        }
        case Object::OBJECT_NULL:
        {
            auto r = std::dynamic_pointer_cast<object::Null>(right);
            return new_bool(true);
        }
        default:
        {
            return new_bool(false);
        }
    }
}