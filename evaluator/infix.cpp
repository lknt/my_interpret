#include <evaluator/evaluator.h>

using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_infix(const std::shared_ptr<ast::Infix> &e) {
    auto left = eval(e->m_left);
    if (is_error(left))
    {
        return left;
    }
    auto right = eval(e->m_right);
    if (is_error(right))
    {
        return right;
    }
    auto op = e->m_operator;
    switch (left->type()) {
        case Object::OBJECT_INTEGER:
        {
            if (right->type() == Object::OBJECT_INTEGER)
            {
                return eval_integer_infix_expression(op, left, right);
            }
            else if (right->type() == Object::OBJECT_FLOAT)
            {
                return eval_float_infix_expression(op, cast_from_integer_to_float(left), right);
            }
        }
        case Object::OBJECT_FLOAT:
        {
            if (right->type() == Object::OBJECT_INTEGER)
            {
                return eval_float_infix_expression(op, left, cast_from_integer_to_float(right));
            }
            else if (right->type() == Object::OBJECT_FLOAT)
            {
                return eval_float_infix_expression(op, left, right);
            }
        }
        default:
            break;
    }
    return new_error("unknown operator: %s %s %s", left->name().c_str() , op.c_str(), right->name().c_str());
}

/*
 * token->ast->object
 * */
std::shared_ptr<Object> Evaluator::eval_integer_infix_expression(const std::string &op,
                                                                 const std::shared_ptr<Object> &left,
                                                                 const std::shared_ptr<Object> &right) {
     auto l = std::dynamic_pointer_cast<object::Integer>(left);
     auto r = std::dynamic_pointer_cast<object::Integer>(right);
     if (op == "+")
     {
         return new_integer(l->m_value + r->m_value);
     }
     else if (op == "-")
     {
         return new_integer(l->m_value - r->m_value);
     }
     else if (op == "*")
     {
         return new_integer(l->m_value * r->m_value);
     }
     else if (op == "/")
     {
         return new_integer(l->m_value / r->m_value);
     }
     else if (op == "%")
     {
         return new_integer(l->m_value % r->m_value);
     }
     else if (op == "&")
     {
         return new_integer(l->m_value & r->m_value);
     }
     else if (op == "|")
     {
         return new_integer(l->m_value | r->m_value);
     }
     else if (op == "^")
     {
         return new_integer(l->m_value ^ r->m_value);
     }
     else if (op == "<<")
     {
         return new_integer(l->m_value << r->m_value);
     }
     else if (op == ">>")
     {
         return new_integer(l->m_value >> r->m_value);
     }
     else if (op == "<")
     {
         return new_bool(l->m_value < r->m_value);
     }else if (op == ">")
     {
         return new_bool(l->m_value > r->m_value);
     }else if (op == "<=")
     {
         return new_bool(l->m_value <= r->m_value);
     }else if (op == ">=")
     {
         return new_bool(l->m_value >= r->m_value);
     }else if (op == "==")
     {
         return new_bool(l->m_value == r->m_value);
     }else if (op == "!=")
     {
         return new_bool(l->m_value != r->m_value);
     }
     return new_error("unknown operator: %s %s %s\n", left->name().c_str(), op.c_str(), right->name().c_str());
}

std::shared_ptr<Object> Evaluator::eval_float_infix_expression(const std::string &op,
                                                                 const std::shared_ptr<Object> &left,
                                                                 const std::shared_ptr<Object> &right) {
    auto l = std::dynamic_pointer_cast<object::Float>(left);
    auto r = std::dynamic_pointer_cast<object::Float>(right);
    if (op == "+")
    {
        return new_float(l->m_value + r->m_value);
    }
    else if (op == "-")
    {
        return new_float(l->m_value - r->m_value);
    }
    else if (op == "*")
    {
        return new_float(l->m_value * r->m_value);
    }
    else if (op == "/")
    {
        return new_float(l->m_value / r->m_value);
    }

    return new_error("unknown operator: %s %s %s\n", left->name().c_str(), op.c_str(), right->name().c_str());
}