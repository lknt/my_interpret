#include <evaluator/evaluator.h>
using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_assign(const std::shared_ptr<ast::Assign> &node,
                                               pi::evaluator::Environment *env) {
    auto obj = eval(node->m_value, env);
    if (is_error(obj))
    {
        return obj;
    }
    switch (node->m_name->type()) {
        case Node::NODE_IDENTIFIER:
        {
            auto e = std::dynamic_pointer_cast<ast::Identifier>(node->m_name);
            env->set(e->m_value, obj);
            return new_null();
        }
        case Node::NODE_INDEX:
        {
            auto e = std::dynamic_pointer_cast<ast::Index>(node->m_name);
            return eval_index_assignment(e, obj, env);
        }
        case Node::NODE_PROPERTY:
        {
            auto e = std::dynamic_pointer_cast<ast::Property>(node->m_name);
            return eval_property_assignment(e, obj, env);
        }
        default:
            break;
    }
    return new_null();
}