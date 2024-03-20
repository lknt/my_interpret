#pragma once

#include <object/object.h>

namespace pi {
    namespace object {
        class Builtin : public Object
        {
        public:
            Builtin() : Object(OBJECT_BUILTIN) {}
            ~Builtin() {}
            //接受一个参数列表，返回一个Obeject
            typedef std::shared_ptr<Object> (Builtin::*method)(const std::vector<std::shared_ptr<Object>>&);
            static std::shared_ptr<Builtin> find(const string & name);
            std::shared_ptr<Object> call(const std::vector<std::shared_ptr<Object>>& args);
        private:
            //内置函数实现
            std::shared_ptr<Object> _print(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _type(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _len(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _int(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _float(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _str(const std::vector<std::shared_ptr<Object>> & args);
            std::shared_ptr<Object> _exit(const std::vector<std::shared_ptr<Object>> & args);

            virtual string str() const
            {
                return "<builtin>";
            }
        public:
            string m_name;
            static std::map<string, method> m_methods;
        };
    }
}