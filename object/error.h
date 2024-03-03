#pragma once

#include <object/object.h>

namespace pi {
    namespace object {
        class Error : public Object
        {
        public:
            Error() : Object(OBJECT_ERROR) {}
            Error(const string & message) : Object(OBJECT_ERROR), m_message(message) {}
            ~Error() {}

            virtual string str()
            {
                return "error: " + m_message;
            }
        public:
            string m_message;
        };
    }

}