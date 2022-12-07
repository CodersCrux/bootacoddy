#ifndef BOOTACODDY_UTIL_TYPES_SET_HPP
#define BOOTACODDY_UTIL_TYPES_SET_HPP

#include "list.hpp"
#include "../../kernel/paging.hpp"

namespace bac::types {

    template<typename SetType>
    class Set : public List<SetType> {
    public:

        virtual void insert(SetType value) override {

            if (this->head == nullptr) {

                this->head = new Node<SetType>(value);
                this->tail = this->head;
                this->_length++;
                return;
            }

            // Loop through list, make sure value doesn't already exist.
            // If it does, just set it.
            Node<SetType> *iter = this->head;
            while (iter) {

                if (iter->value == value) {
                    // This may look ridiculously pointless, but it helps with dictionary pairs.
                    iter->value = value;
                    return;
                }
                iter = iter->next;
            }

            this->tail->next = new Node<SetType>(value);
            this->tail = this->tail->next;
            this->_length++;
        }

    };

}

#endif
