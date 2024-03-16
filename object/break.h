#pragma once

#include <object/object.h>

namespace pi {
    namespace object {
        class Break : public Object
        {
        public:
            Break() : Object(OBJECT_BREAK) {}
            ~Break() {}

            virtual string str() const
            {
                return "break";
            }

        };
    }
}