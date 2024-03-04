#include <evaluator/evaluator.h>

using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_infix(const std::string &op, const std::shared_ptr<Object> &left,
                                              const std::shared_ptr<Object> &right, Environment * env)  {

    switch (left->type()) {
        case Object::OBJECT_BOOL:
        {
            if (right->type() == Object::OBJECT_BOOL)
            {
                return eval_bool_infix_expression(op, left, right);
            }
            else if (right->type() == Object::OBJECT_INTEGER)
            {
                return eval_integer_infix_expression(op, left, right);
            }
            else
            {
                return eval_diff_type_operator_expression(op, left, right);
            }
        }
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
            else if (right->type() == Object::OBJECT_BOOL)
            {
                return eval_integer_infix_expression(op, left, right);
            }
            else if (right->type() == Object::OBJECT_STRING)
            {
                return eval_string_integer_infix_expression(op, right, left);
            }
            else
            {
                return eval_diff_type_operator_expression(op, left, right);
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
            else
            {
                return eval_diff_type_operator_expression(op, left, right);
            }
        }
        case Object::OBJECT_STRING:
        {
            if (right->type() == Object::OBJECT_STRING)
            {
                return eval_string_infix_expression(op, left, right);
            }
            else if (right->type() == Object::OBJECT_INTEGER)
            {
                return eval_string_integer_infix_expression(op, left, right);
            }
            else
            {
                return eval_diff_type_operator_expression(op, left, right);
            }
        }
        case Object::OBJECT_NULL:
        {
            if (right->type() == Object::OBJECT_NULL)
            {
                return eval_null_infix_expression(op, left, right);
            }
            else
            {
                return eval_diff_type_operator_expression(op, left, right);
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
     }
     else if (op == ">")
     {
         return new_bool(l->m_value > r->m_value);
     }
     else if (op == "<=")
     {
         return new_bool(l->m_value <= r->m_value);
     }
     else if (op == ">=")
     {
         return new_bool(l->m_value >= r->m_value);
     }
     else if (op == "==")
     {
         return new_bool(l->m_value == r->m_value);
     }
     else if (op == "!=")
     {
         return new_bool(l->m_value != r->m_value);
     }
    if (op == "&&")
    {
        return new_bool(l->m_value && r->m_value);
    }
    else if (op == "||")
    {
        return new_bool(l->m_value || r->m_value);
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


std::shared_ptr<Object> Evaluator::eval_bool_infix_expression(const std::string &op,
                                                               const std::shared_ptr<Object> &left,
                                                               const std::shared_ptr<Object> &right) {
    auto l = std::dynamic_pointer_cast<object::Bool>(left);
    auto r = std::dynamic_pointer_cast<object::Bool>(right);
    if (op == "&&")
    {
        return new_bool(l->m_value && r->m_value);
    }
    else if (op == "||")
    {
        return new_bool(l->m_value || r->m_value);
    }


    return new_error("unknown operator: %s %s %s\n", left->name().c_str(), op.c_str(), right->name().c_str());
}

std::shared_ptr<Object> Evaluator::eval_string_infix_expression(const std::string &op,
                                                                const std::shared_ptr<Object> &left,
                                                                const std::shared_ptr<Object> &right) {
    auto l = std::dynamic_pointer_cast<object::String>(left);
    auto r = std::dynamic_pointer_cast<object::String>(right);
    if (op == "+")
    {
        return new_string(l->m_value + r->m_value);
    }
    else if (op == "==")
    {
        return new_bool(l->m_value == r->m_value);
    }
    else if (op == "!=")
    {
        return new_bool(l->m_value == r->m_value);
    }
    else if (op == "<")
    {
        return new_bool(l->m_value < r->m_value);
    }
    else if (op == "<=")
    {
        return new_bool(l->m_value <= r->m_value);
    }
    else if (op == ">")
    {
        return new_bool(l->m_value > r->m_value);
    }
    else if (op == ">=")
    {
        return new_bool(l->m_value >= r->m_value);
    }
    return new_error("unknown operator: %s %s %s\n", left->name().c_str(), op.c_str(), right->name().c_str());
}

std::shared_ptr<Object> Evaluator::eval_string_integer_infix_expression(const std::string &op,
                                                                        const std::shared_ptr<Object> &left,
                                                                        const std::shared_ptr<Object> &right) {
    auto l = std::dynamic_pointer_cast<object::String>(left);
    auto r = std::dynamic_pointer_cast<object::Integer>(right);
    if (op == "*")
    {
        string str;
        for (int i = 0; i < r->m_value; i ++)
        {
            str += l->m_value;
        }
        return new_string(str);
    }
    return new_error("unknown operator: %s %s %s\n", left->name().c_str(), op.c_str(), right->name().c_str());
}

std::shared_ptr<Object> Evaluator::eval_null_infix_expression(const std::string &op,
                                                              const std::shared_ptr<Object> &left,
                                                              const std::shared_ptr<Object> &right) {
    if (op == "==")
    {
        return new_bool(true);
    }
    else if (op == "!=")
    {
        return new_bool(false);
    }

    return new_error("unknown operator: %s %s %s\n", left->name().c_str(), op.c_str(), right->name().c_str());
}

std::shared_ptr<Object> Evaluator::eval_diff_type_operator_expression(const std::string &op,
                                                                      const std::shared_ptr<Object> &left,
                                                                      const std::shared_ptr<Object> &right) {
    if (op == "==")
    {
        return new_bool(false);
    }
    else if (op == "!=")
    {
        return new_bool(true);
    }

    return new_error("unknown operator: %s %s %s\n", left->name().c_str(), op.c_str(), right->name().c_str());
}