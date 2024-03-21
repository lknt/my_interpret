#pragma once

#include <object/object.h>


namespace pi
{
    namespace object
    {
        class Iterable
        {
        public:
            virtual std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>> next() = 0;
            virtual void reset() = 0;
        };
    }
}