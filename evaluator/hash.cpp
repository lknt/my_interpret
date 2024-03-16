#include <evaluator/evaluator.h>
using namespace pi::evaluator;

std::shared_ptr<Object> Evaluator::eval_hash(const std::shared_ptr<ast::Hash> &node, pi::evaluator::Environment *env) {
    std::shared_ptr<object::Hash> hash(new object::Hash());
    for (auto & pair : node->m_pairs)
    {
        auto key = eval(pair.first, env);
        if (is_error(key))
        {
            return key;
        }
        auto hashable = std::dynamic_pointer_cast<Hashable>(key);
        if (!hashable)
        {
            return new_error("object not support hashable: %s", key->name().c_str());

        }
        auto val = eval(pair.second, env);
        if (is_error(val))
        {
            return val;
        }

        HashPair hash_pair;
        hash_pair.m_key = key;
        hash_pair.m_value = val;
//        printf("%llu\n", hashable->hash().m_value);
//        printf("%s\n", hash_pair.m_value->str().c_str());

        hash->m_pairs[hashable->hash()] = hash_pair;
//        printf("%llu\n", hashable->hash().m_value);
    }
    return hash;
}