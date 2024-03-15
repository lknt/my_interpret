#include <evaluator/evaluator.h>
using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_index_expression(const std::shared_ptr<ast::Index> & node, Environment * env)
{
    auto left = eval(node->m_left, env);
    if (is_error(left))
    {
        return left;
    }
    auto index = eval(node->m_index, env);
    if (is_error(index))
    {
        return index;
    }
    if (left->type() == Object::OBJECT_LIST && index->type() == Object::OBJECT_INTEGER)
    {
        return eval_list_index_expression(left, index, env);
    }
    return new_error("index operator not support: %s[%s]", left->name().c_str(), index->str().c_str());
}
std::shared_ptr<Object> Evaluator::eval_list_index_expression(const std::shared_ptr<Object> & left, const std::shared_ptr<Object> & index, Environment * env)
{
    if (left->type() != Object::OBJECT_LIST)
    {
        return new_error(("left object is not list"));
    }
    if (index->type() != Object::OBJECT_INTEGER)
    {
        return new_error(("index object is not integer"));
    }
    auto l = std::dynamic_pointer_cast<object::List>(left);
    auto i = std::dynamic_pointer_cast<object::Integer>(index);
    auto idx = i->m_value;
    auto max = (int64_t)(l->m_elements.size() - 1);
    if (idx < -(max + 1) || idx > max)
    {
        return new_error("list index out of range");
    }
    if (idx < 0)
    {
        idx += (max + 1);
    }
    return l->m_elements[idx];
}
