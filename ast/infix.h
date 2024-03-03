#pragma once

#include <ast/node.h>

namespace pi {
    namespace ast {
        /*
         * Infix类继承自Expression
         * 是一个中缀表达式，是属于表达式的
         * 公有方法
         * 构造函数直接调用Expression的，type传NODE_INFIX
         * 重写json函数，把type和value写进去
         * 公有成员变量
         * int64_t m_values;
         * */
        class Infix : public Expression
        {
        public:
            Infix() : Expression(NODE_INFIX){}
            ~Infix() {}
            Json json() override
            {
                Json json;
                json["type"] = name();
                json["right"] = m_right->json();
                json["operator"] = m_operator;
                json["left"] = m_left->json();
                return json;
            }

        public:
            std::shared_ptr<Expression> m_left;
            string m_operator;
            std::shared_ptr<Expression> m_right;
        };

    }

}