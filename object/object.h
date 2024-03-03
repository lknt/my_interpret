//
// Created by ROG on 2024-02-26.
//

#pragma once
#include <map>
#include <memory>
#include <string>
#include <cstdarg>
using std::string;

namespace pi
{
    namespace object
    {
        /*
         * 数据类型的基类
         * 公有方法
         * 首先enum Type，现在有错误类型OBJECT_ERROR,整形OBJECT_INTEGER
         * 空构造函数
         * 传入type的构造函数
         * 虚析构函数（因为要实现多态
         * 获取类型type，名字name函数
         * 虚函数str()用于转换Object成srting
         *
         * 保护成员变量
         * 类型m_type
         * std::map<Type, string> m_names;
         *
         * */
        class Object
        {
        public:
            enum Type
            {
                OBJECT_ERROR = 0,
                OBJECT_INTEGER,
                OBJECT_FLOAT,
            };
            Object(){}
            Object(Type type) : m_type(type) {}
            virtual ~Object() {}

            Type type() const {return m_type;}
            string name() const;
            virtual string str() = 0;

            static std::shared_ptr<Object> new_error(const char * format, ...);
            static std::shared_ptr<Object> new_integer(int64_t value);
            static std::shared_ptr<Object> new_float(double value);


        protected:
            Type m_type;
            int64_t m_value;
            static std::map<Type, string> m_names;
        };
    }
}