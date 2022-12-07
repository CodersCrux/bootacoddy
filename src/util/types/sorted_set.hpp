#ifndef BOOTACODDY_UTIL_TYPES_SORTED_SET_HPP
#define BOOTACODDY_UTIL_TYPES_SORTED_SET_HPP

#include "list.hpp"
#include "../../kernel/paging.hpp"
#include "set.hpp"

namespace bac::types {

    template<typename SetType>
    class SortedSet : public Set<SetType> {
    public:

        void insert(SetType value) override {

            if (this->head == nullptr) {

                this->head = new Node<SetType>(value);
                this->tail = this->head;
                this->_length++;
                return;
            }

            if (this->head->value > value) {

                Node<SetType> *node = new Node<SetType>(value, this->head);
                this->head = node;
                this->_length++;
                return;
            }

            if (this->tail->value < value) {

                Node<SetType> *node = new Node<SetType>(value);
                this->tail->next = node;
                this->tail = node;
                this->_length++;
                return;
            }

            Node<SetType> *iter = this->head;
            while (iter->value != value && iter->next) {

                if (iter->next->value > value) {

                    Node<SetType> *node = new Node<SetType>(value, iter->next);
                    iter->next = node;
                    this->_length++;
                    return;
                }

                iter = iter->next;
            }

            iter->value = value;
        }

    };

}

#endif
