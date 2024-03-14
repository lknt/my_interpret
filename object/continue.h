#pragma once

#include <object/object.h>

namespace pi {
    namespace object {
        class Continue : public Object
        {
        public:
            Continue() : Object(OBJECT_CONTINUE) {}
            ~Continue() {}

            virtual string str()
            {
                return "continue";
            }

        };
    }
}