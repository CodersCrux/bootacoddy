#ifndef BOOTACODDY_UTIL_TYPES_DICTIONARY_HPP
#define BOOTACODDY_UTIL_TYPES_DICTIONARY_HPP

#include "../../util/types.h"
#include "list.hpp"
#include "set.hpp"
#include "dictionary_pair.hpp"

namespace bac::types {

    template<typename KeyType, typename ValueType>
    class Dictionary: public Set<DictionaryPair<KeyType, ValueType>> {
    public:

        void set(KeyType key, ValueType value) {
            this->insert(DictionaryPair(key, value));
        }

        ValueType& get(KeyType key) {

            for (DictionaryPair<KeyType, ValueType> item: this)
                if (item.key == key)
                    return item.value;
            PANIC("Key does not exist in dictionary.");
            return 0;
        }

        ValueType& operator[](KeyType key) {
            return get(key);
        }
    };

}

#endif

