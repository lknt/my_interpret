//
// Created by ROG on 2024-02-26.
//
#include <object/header.h>



using namespace pi::object;

std::map<Object::Type, string> Object::m_names = {
        {OBJECT_ERROR, "error"},
        {OBJECT_INTEGER, "integer"},
        {OBJECT_FLOAT, "float"},
        {OBJECT_BOOL, "bool"},
        {OBJECT_STRING, "string"},
        {OBJECT_NULL, "null"},
        {OBJECT_BREAK, "break"},
        {OBJECT_CONTINUE, "continue"},
        {OBJECT_LIST, "list"},
        {OBJECT_HASH, "hash"},
        {OBJECT_FUNCTION, "function"},
        {OBJECT_RETURN, "return"},
};

string Object::name() const {
    auto it = m_names.find(m_type);
    if (it != m_names.end())
    {
        return it->second;
    }
    return "";
}

std::shared_ptr<Object> Object::new_error(const char *format, ...) {
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

std::shared_ptr<Object> Object::new_integer(int64_t value) {
    return std::make_shared<Integer>(value);
}

std::shared_ptr<Object> Object::new_float(double value) {
    return std::make_shared<Float>(value);
}

std::shared_ptr<Object> Object::new_bool(bool value) {
    return std::make_shared<Bool>(value);
}

std::shared_ptr<Object> Object::new_string(std::string value) {
    return std::make_shared<String>(value);
}
std::shared_ptr<Object> Object::new_null() {
    return std::make_shared<Null>();
}

std::shared_ptr<Object> Object::new_break() {
    return std::make_shared<Break>();
}

std::shared_ptr<Object> Object::new_continue() {
    return std::make_shared<Continue>();
}