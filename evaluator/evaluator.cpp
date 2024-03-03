//
// Created by ROG on 2024-03-01.
//

#include <evaluator/evaluator.h>
using namespace pi::evaluator;

bool Evaluator::is_error(const std::shared_ptr<Object> &obj)
{
    return obj->type() == Object::OBJECT_ERROR;
}
std::shared_ptr<Object> Evaluator::new_error(const char * format, ...)
{
    char buf[1024] = {0};
    va_list arg_ptr;
    va_start(arg_ptr, format);
    //arg_ptr获得format后面的所有参数
    vsnprintf(buf, sizeof buf, format, arg_ptr);
    va_end(arg_ptr);

    std::shared_ptr<Error> obj(new Error());
    obj->m_message = buf;
    return obj;
}

std::shared_ptr<Object> Evaluator::new_integer(int64_t value)
{
    return Object::new_integer(value);
}

std::shared_ptr<Object> Evaluator::new_float(double value)
{
    return Object::new_float(value);
}

std::shared_ptr<Object> Evaluator::cast_from_integer_to_float(const std::shared_ptr<Object> & obj)
{
    auto i = std::dynamic_pointer_cast<object::Integer>(obj);
    return new_float(double(i->m_value));
}


std::shared_ptr<Object> Evaluator::eval(const std::shared_ptr<ast::Node> &node) {
    switch (node->type()) {
        case Node::NODE_PROGRAM:
        {
            //对程序根节点求值
            //dynamic_cast面向裸指针，dynamic_pointer_cast面向智能指针
            auto s = std::dynamic_pointer_cast<ast::Program>(node);
            return eval_program(s->m_statement);
        }
        case Node::NODE_EXPRESSION_STATEMENT:
        {
            auto s = std::dynamic_pointer_cast<ast::Expression_Statement>(node);
            return eval(s->m_expression);
        }
        case Node::NODE_INTEGER:
        {
            auto e = std::dynamic_pointer_cast<ast::Integer>(node);
            return eval_integer(e);
        }
        case Node::NODE_FLOAT:
        {
            auto e = std::dynamic_pointer_cast<ast::Float>(node);
            return eval_float(e);
        }
        case Node::NODE_INFIX:
        {
            /*
             * 解析左右，然后把符号，左右的value（object）传入eval_infix里面*/
            auto e = std::dynamic_pointer_cast<ast::Infix>(node);

            return eval_infix(e);

        }
        case Node::NODE_PREFIX:
        {
            /*
             * Expression->prefix*/
            auto e = std::dynamic_pointer_cast<ast::Prefix>(node);
            return eval_prefix(e);
        }
        default:
        {
            return new_error("node type error");
        }

    }
}