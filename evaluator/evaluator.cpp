//
// Created by ROG on 2024-03-01.
//

#include <evaluator/evaluator.h>
using namespace pi::evaluator;

bool Evaluator::is_error(const std::shared_ptr<Object> &obj)
{
    return obj->type() == Object::OBJECT_ERROR;
}

bool Evaluator::is_true(const std::shared_ptr<Object> &obj) {
    switch (obj->type()) {
        case Object::OBJECT_NULL:
        {
            return false;
        }
        case Object::OBJECT_BOOL:
        {
            auto b = std::dynamic_pointer_cast<object::Bool>(obj);
            return b->m_value == true;
        }
    }

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

std::shared_ptr<Object> Evaluator::new_bool(bool value)
{
    return Object::new_bool(value);
}
std::shared_ptr<Object> Evaluator::new_string(std::string value) {
    return Object::new_string(value);
}

std::shared_ptr<Object> Evaluator::new_null() {
    return Object::new_null();
}

std::shared_ptr<Object> Evaluator::new_break() {
    return Object::new_break();
}

std::shared_ptr<Object> Evaluator::new_continue() {
    return Object::new_continue();
}

std::shared_ptr<Object> Evaluator::cast_from_integer_to_float(const std::shared_ptr<Object> & obj)
{
    auto i = std::dynamic_pointer_cast<object::Integer>(obj);
    return new_float(double(i->m_value));
}


std::shared_ptr<Object> Evaluator::eval(const std::shared_ptr<ast::Node> &node, pi::evaluator::Environment *env) {
    switch (node->type()) {
        case Node::NODE_PROGRAM:
        {
            //对程序根节点求值
            //dynamic_cast面向裸指针，dynamic_pointer_cast面向智能指针
            auto s = std::dynamic_pointer_cast<ast::Program>(node);
            return eval_program(s->m_statement, env);
        }
        case Node::NODE_EXPRESSION_STATEMENT:
        {
            auto s = std::dynamic_pointer_cast<ast::Expression_Statement>(node);
            return eval(s->m_expression, env);
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
        case Node::NODE_STRING:
        {
            auto e = std::dynamic_pointer_cast<ast::String>(node);
            return eval_string(e);
        }
        case Node::NODE_BOOL:
        {
            auto e = std::dynamic_pointer_cast<ast::Bool>(node);
            return eval_bool(e);
        }
        case Node::NODE_NULL:
        {
            auto e = std::dynamic_pointer_cast<ast::Null>(node);
            return eval_null();
        }
        case Node::NODE_INFIX:
        {
            /*
             * 解析左右，然后把符号，左右的value（object）传入eval_infix里面*/
            auto e = std::dynamic_pointer_cast<ast::Infix>(node);
            auto left = eval(e->m_left, env);
            if (is_error(left))
            {
                return left;
            }
            auto right = eval(e->m_right, env);
            if (is_error(right))
            {
                return right;
            }
            auto op = e->m_operator;


            return eval_infix(op, left, right, env);

        }
        case Node::NODE_PREFIX:
        {
            /*
             * Expression->prefix*/
            auto e = std::dynamic_pointer_cast<ast::Prefix>(node);
            return eval_prefix(e, env);
        }
        case Node::NODE_POSTFIX:
        {
            /*
             * Expression->prefix*/
            auto e = std::dynamic_pointer_cast<ast::Postfix>(node);
            return eval_postfix(e, env);
        }
        case Node::NODE_IDENTIFIER:
        {
            auto e = std::dynamic_pointer_cast<ast::Identifier>(node);
            return eval_identifier(e, env);
        }
        case Node::NODE_ASSIGN:
        {
            auto e = std::dynamic_pointer_cast<ast::Assign>(node);
            return eval_assign(e, env);
        }
        case Node::NODE_COMPOUND:
        {
            auto e = std::dynamic_pointer_cast<ast::Compound>(node);
            return eval_compound(e, env);
        }
        case Node::NODE_TERNARY:
        {
            auto e = std::dynamic_pointer_cast<ast::Ternary>(node);
            return eval_ternary(e, env);
        }
        case Node::NODE_BLOCK:
        {
            auto e = std::dynamic_pointer_cast<ast::Block>(node);
            return eval_block(e, env);
        }
        case Node::NODE_IF:
        {
            auto e = std::dynamic_pointer_cast<ast::If>(node);
            return eval_if(e, env);
        }
        case Node::NODE_BREAK:
        {
            auto e = std::dynamic_pointer_cast<ast::Break>(node);
            return eval_break(e);
        }
        case Node::NODE_CONTINUE:
        {
            auto e = std::dynamic_pointer_cast<ast::Continue>(node);
            return eval_continue(e);
        }
        case Node::NODE_WHILE:
        {
            auto e = std::dynamic_pointer_cast<ast::While>(node);
            return eval_while(e, env);
        }
        case Node::NODE_FOR:
        {
            auto e = std::dynamic_pointer_cast<ast::For>(node);
            return eval_for(e, env);
        }
        case Node::NODE_SWITCH:
        {
            auto e = std::dynamic_pointer_cast<ast::Switch>(node);
            return eval_switch(e, env);
        }
        case Node::NODE_LIST:
        {
            auto e = std::dynamic_pointer_cast<ast::List>(node);
            return eval_list(e, env);
        }
        case Node::NODE_INDEX:
        {
            auto e = std::dynamic_pointer_cast<ast::Index>(node);
            return eval_index_expression(e, env);
        }
        case Node::NODE_HASH:
        {
            auto e = std::dynamic_pointer_cast<ast::Hash>(node);
            return eval_hash(e, env);
        }
        default:
        {
            return new_error("node type error");
        }

    }
}