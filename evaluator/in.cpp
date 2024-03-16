#include <evaluator/evaluator.h>
using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_in(const std::shared_ptr<ast::In> & node, Environment * env)
{
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
    switch (right->type()) {
        case Object::OBJECT_STRING:
        {
            return eval_in_string(left,right);
        }
        case Object::OBJECT_LIST:
        {
            return eval_in_list(left,right);
        }
        case Object::OBJECT_HASH:
        {
            return eval_in_hash(left,right);
        }
        default:
            break;
    }
    return new_error("in operator not support %s", right->name().c_str());
}
std::shared_ptr<Object> Evaluator::eval_in_string(const std::shared_ptr<Object> & left,const std::shared_ptr<Object> & right)
{
    if (left->type() != Object::OBJECT_STRING)
    {
        return new_bool(false);
    }
    auto l = std::dynamic_pointer_cast<object::String>(left);
    auto r = std::dynamic_pointer_cast<object::String>(right);
    auto pos = r->m_value.find(l->m_value);
    if (pos == std::string::npos)
    {
        return new_bool(false);
    }
    return new_bool(true);
}
std::shared_ptr<Object> Evaluator::eval_in_list(const std::shared_ptr<Object> & left,const std::shared_ptr<Object> & right)
{
    auto list = std::dynamic_pointer_cast<object::List>(right);

    for (auto & elem : list->m_elements)
    {
        if ((left->type() == elem->type()) && (left->str() == elem->str()))
        {
            return new_bool(true);
        }
    }
    return new_bool(false);
}
std::shared_ptr<Object> Evaluator::eval_in_hash(const std::shared_ptr<Object> & left,const std::shared_ptr<Object> & right)
{
    auto hash = std::dynamic_pointer_cast<object::Hash>(right);
    auto hashable = std::dynamic_pointer_cast<Hashable>(left);
    if (!hashable)
    {
        return new_error("object not support hashable: %s", left->name().c_str());
    }
    auto it = hash->m_pairs.find(hashable->hash());
    if (it != hash->m_pairs.end())
    {
        return new_bool(true);
    }
    return new_bool(false);
}
