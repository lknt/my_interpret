#include <evaluator/evaluator.h>

using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_property_expression(const std::shared_ptr<ast::Property> &node,
                                                            pi::evaluator::Environment *env)
{
    auto left = eval(node->m_object, env);
    if (is_error(left)){
        return left;
    }
    if (node->m_property->type() != Node::NODE_IDENTIFIER)
    {
        return new_error("property object is not identifier");
    }
    auto prop = std::dynamic_pointer_cast<ast::Identifier>(node->m_property);
    std::shared_ptr<object::String> index(new object::String(prop->m_value));
    switch (left->type()) {
        case Object::OBJECT_HASH:
        {
            return eval_hash_index_expression(left, index);
        }
        default:
            break;
    }
    return new_error("invalid property %s on %s", prop->m_value.c_str(), left->name().c_str());
}