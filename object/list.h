#pragma once

#include <object/object.h>


namespace pi
{
    namespace object
    {
        class List : public Object
        {
        public:
            List() : Object(OBJECT_LIST) {}
            ~List() {}
            virtual string str() const;
        public:
            std::vector<std::shared_ptr<Object>> m_elements;
        };
    }
}