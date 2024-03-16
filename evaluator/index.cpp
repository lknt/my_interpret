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
    switch (left->type()) {
        case Object::OBJECT_LIST:
        {
            if (index->type() == Object::OBJECT_INTEGER)
            {
                return eval_list_index_expression(left, index);
            }
        }
        case Object::OBJECT_STRING:
        {
            if (index->type() == Object::OBJECT_INTEGER)
            {
                return eval_string_index_expression(left, index);
            }
        }

    }
    return new_error("index operator not support: %s[%s]", left->name().c_str(), index->str().c_str());
}
std::shared_ptr<Object> Evaluator::eval_list_index_expression(const std::shared_ptr<Object> & left, const std::shared_ptr<Object> & index)
{
    auto l = std::dynamic_pointer_cast<object::List>(left);
    auto i = std::dynamic_pointer_cast<object::Integer>(index);
    auto idx = i->m_value;
    auto max = (int64_t)(l->m_elements.size());
    if (idx < -max || idx >= max)
    {
        return new_error("list index out of range");
    }
    if (idx < 0)
    {
        idx += max;
    }
    return l->m_elements[idx];
}

std::shared_ptr<Object> Evaluator::eval_string_index_expression(const std::shared_ptr<Object> & left, const std::shared_ptr<Object> & index)
{
    auto l = std::dynamic_pointer_cast<object::String>(left);
    auto i = std::dynamic_pointer_cast<object::Integer>(index);
    auto idx = i->m_value;
    auto max = (int64_t)(l->m_value.size());
    if (idx < -max || idx > max)
    {
        return new_error("string index out of range");
    }
    if (idx < 0)
    {
        idx += max;
    }
    string val;
    val = l->m_value[idx];
    return new_string(val);
}

//index assign
std::shared_ptr<Object> Evaluator::eval_index_assignment(const std::shared_ptr<ast::Index> &name,
                                                         const std::shared_ptr<Object> &val,
                                                         pi::evaluator::Environment *env) {
    auto left = eval(name->m_left, env);
    if (is_error(left))
    {
        return left;
    }
    auto index = eval(name->m_index, env);
    if (is_error(index))
    {
        return index;
    }
    switch (left->type())
    {
        case Object::OBJECT_LIST:
        {
            return eval_list_index_assignment(left, index, val);
        }
        default:
            break;
    }
    return new_error("index assignment error: %s", left->name().c_str());
}
std::shared_ptr<Object> Evaluator::eval_list_index_assignment(const std::shared_ptr<Object> & left, const std::shared_ptr<Object> & index, const std::shared_ptr<Object> & val)
{
    auto l = std::dynamic_pointer_cast<object::List>(left);
    if (index->type() != Object::OBJECT_INTEGER)
    {
        return new_error("index object is not support");
    }
    auto i = std::dynamic_pointer_cast<object::Integer>(index);
    auto idx = i->m_value;
    auto max = (int64_t)(l->m_elements.size());
    if (idx < 0)
    {
        idx += max;
        if (idx < 0 || idx >= max)
        {
            return new_error("index out of range: %d", idx);
        }
    }
    if (idx >= max)
    {
        for (auto k = max; k < idx; k ++)
        {
            l->m_elements.push_back(new_null());
        }
        l->m_elements.push_back(val);
    }
    else
    {
        l->m_elements[idx] = val;
    }
    return new_null();

}
