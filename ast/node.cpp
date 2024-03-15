#include <ast/node.h>
using namespace pi::ast;

std::map<Node::Type, string> Node::m_names = {
        {NODE_INTEGER, "Integer"},
        {NODE_FLOAT, "Float"},
        {NODE_BOOL, "Bool"},
        {NODE_INFIX, "Infix"},
        {NODE_EXPRESSION_STATEMENT, "Expression"},
        {NODE_PROGRAM, "Program"},
        {NODE_PREFIX, "Prefix"},
        {NODE_STRING, "String"},
        {NODE_NULL, "Null"},
        {NODE_IDENTIFIER, "identifier"},
        {NODE_ASSIGN, "Assign"},
        {NODE_COMPOUND, "Compound"},
        {NODE_POSTFIX, "Postfix"},
        {NODE_TERNARY, "Ternary"},
        {NODE_BLOCK, "Block"},
        {NODE_IF, "If"},
        {NODE_SCENARIO, "Scenario"},

        {NODE_WHILE, "While"},
        {NODE_BREAK, "Break"},
        {NODE_CONTINUE, "Continue"},

        {NODE_FOR, "For"},
        {NODE_SWITCH, "Switch"},
        {NODE_CASE, "Case"},


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

