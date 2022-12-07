#ifndef BOOTACODDY_UTIL_TYPES_SORTED_LIST_HPP
#define BOOTACODDY_UTIL_TYPES_SORTED_LIST_HPP

#include "list.hpp"

namespace bac::types {

    template<typename ListType>
    class SortedList: public List<ListType> {

        void insert(ListType value) override {

            this->_length++;

            if (this->head == nullptr) {

                this->head = new Node<ListType>();
                this->head->value = value;
                this->tail = this->head;
                return;
            }

            if (this->head->value >= value) {

                Node<ListType> *node = new Node<ListType>();
                node->value = value;
                node->next = this->head;
                this->head = node;
                return;
            }

            Node<ListType> *iter = this->head;
            while (iter->next && iter->next->value < value)
                iter = iter->next;

            Node<ListType> *node = new Node<ListType>(value, iter->next);
            iter->next = node;

            // 2 - 4 - 5 - 9 - 14
        }

    };

}

#endif