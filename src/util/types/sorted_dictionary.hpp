#ifndef BOOTACODDY_UTIL_TYPES_SORTED_DICTIONARY_HPP
#define BOOTACODDY_UTIL_TYPES_SORTED_DICTIONARY_HPP

#include "../../util/types.h"
#include "sorted_set.hpp"
#include "dictionary_pair.hpp"

namespace bac::types {

    template<typename KeyType, typename ValueType>
    class SortedDictionary: public SortedSet<DictionaryPair<KeyType, ValueType>> {
    public:

        void set(KeyType key, ValueType value) {
            this->insert(DictionaryPair(key, value));
        }

        Node<DictionaryPair<KeyType, ValueType>> *get_node(KeyType key) {

            Node<DictionaryPair<KeyType, ValueType>> *iter = this->head;
            while (iter) {

                if (iter->value.key == key)
                    return iter;
                iter = iter->next;
            }

            return 0;
        }

        ValueType get(KeyType key) {
            return get_node(key)->value;
        }

        ValueType operator[](KeyType key) {
            return get(key);
        }
    };

}

#endif

