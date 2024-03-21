#pragma once

#include <object/object.h>

namespace pi
{
    namespace object
    {
        class Copyable
        {
        public:
            virtual std::shared_ptr<Object> copy() = 0;
        };
    }
}
