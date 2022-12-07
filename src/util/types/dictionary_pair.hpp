#ifndef BOOTACODDY_UTIL_TYPES_DICTIONARY_PAIR
#define BOOTACODDY_UTIL_TYPES_DICTIONARY_PAIR

namespace bac::types {

    template<typename PairKeyType, typename PairValueType>
    struct DictionaryPair {

        DictionaryPair(PairKeyType key, PairValueType value)
                : key(key), value(value) {}

        PairKeyType key;
        PairValueType value;

        bool operator<(DictionaryPair<PairKeyType, PairValueType> other) {
            return key < other.key;
        }

        bool operator<=(DictionaryPair<PairKeyType, PairValueType> other) {
            return key <= other.key;
        }

        bool operator>(DictionaryPair<PairKeyType, PairValueType> other) {
            return key > other.key;
        }

        bool operator>=(DictionaryPair<PairKeyType, PairValueType> other) {
            return key >= other.key;
        }

        bool operator==(DictionaryPair<PairKeyType, PairValueType> other) {
            return key == other.key;
        }

        bool operator!=(DictionaryPair<PairKeyType, PairValueType> other) {
            return key != other.key;
        }
    };
}

#endif