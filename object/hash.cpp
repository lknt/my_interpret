#include <object/hash.h>
using namespace pi::object;

string Hash::str() const
{
    string s;
    s += "{";
    for (auto it = m_pairs.begin(); it != m_pairs.end(); it ++)
    {
        if (it != m_pairs.begin())
        {
            s += ", ";
        }
        auto key = it->second.m_key;
        auto val = it->second.m_value;
        if (key->type() == OBJECT_STRING)
        {
            s += "\""+ key->str() + "\"";
        }
        else
        {
            s += key->str();
        }
        s += ": ";
        if (val->type() == OBJECT_STRING)
        {
            s += "\""+ val->str() + "\"";
        }
        else
        {
            s += val->str();
        }
    }
    s += "}";
    return s;
}