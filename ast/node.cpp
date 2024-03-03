#include <ast/node.h>
using namespace pi::ast;

std::map<Node::Type, string> Node::m_names = {
        {NODE_INTEGER, "Integer"},
        {NODE_FLOAT, "Float"},
        {NODE_INFIX, "Infix"},
        {NODE_EXPRESSION_STATEMENT, "Expression"},
        {NODE_PROGRAM, "Program"},
        {NODE_PREFIX, "Prefix"}

};

string Node::name() const
{
    auto it = m_names.find(m_type);
    if (it != m_names.end())
    {
        return it->second;
    }
    return "";
}
