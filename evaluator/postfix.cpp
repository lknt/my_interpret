#include <evaluator/evaluator.h>

using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_postfix(const std::shared_ptr<ast::Postfix> &node,
                                                pi::evaluator::Environment *env) {
    string op = node->m_operator;
    auto left = eval(node->m_left, env);
    if (is_error(left))
    {
        return left;
    }
    std::shared_ptr<Object> val;

    if(left->type() == Object::OBJECT_INTEGER)
    {
        auto i = std::dynamic_pointer_cast<object::Integer>(left);
        if (op == "++")
        {
            val = new_integer(i->m_value + 1);
        }
        else if (op == "--")
        {
            val = new_integer(i->m_value - 1);
        }
        else
        {
            return new_error("postfix operator not support:%s %s", op.c_str(), left->name().c_str());

        }
    }
    else if(left->type() == Object::OBJECT_FLOAT)
    {
        auto f = std::dynamic_pointer_cast<object::Float>(left);
        if (op == "++")
        {
            val = new_float(f->m_value + 1);
        }
        else if (op == "--")
        {
            val = new_float(f->m_value - 1);
        }
        else
        {
            return new_error("postfix operator not support:%s %s", op.c_str(), left->name().c_str());

        }
    }
    switch (node->m_left->type()) {
        case Node::NODE_IDENTIFIER:
        {
            auto expr = std::dynamic_pointer_cast<ast::Identifier>(node->m_left);
            env->set(expr->m_value, val);
            break;
        }
        default:
            break;
    }

    return left;

}

