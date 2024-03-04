#pragma once

#include <object/object.h>

namespace pi
{
    namespace object
    {
        class Null : public Object
        {
        public:
            Null() : Object(OBJECT_NULL) {}
           ~Null() {}
            virtual string str()
            {
                return "null";
            }

        };
    }
}