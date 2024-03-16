#include <object/list.h>

using namespace pi::object;

string List::str() const
{
    string s;
    s += "[";
    for (int i = 0; i < m_elements.size(); i ++)
    {
        if (i > 0)
        {
            s += ", ";
        }
        auto obj = m_elements[i];
        if (obj->type() == Object::OBJECT_STRING)
        {
            s += "\"" + obj->str() + "\"";
        }
        else
        {
            s += obj->str();
        }
    }
    s += "]";
    return s;
}