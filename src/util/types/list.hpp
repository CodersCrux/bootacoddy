#ifndef BOOTACODDY_UTIL_TYPES_LIST_HPP
#define BOOTACODDY_UTIL_TYPES_LIST_HPP

#include "../types.h"
#include "node.hpp"

namespace bac::types {

    template<typename ListType>
    class List {
    public:

        class Iterator {
        public:

            Iterator(const Node<ListType> *node) : currentNode(node) {}

            Iterator &operator=(Node<ListType> *node) {

                this->currentNode = node;
                return *this;
            }

            Iterator &operator++() {

                if (currentNode)
                    currentNode = currentNode->next;
                return *this;
            }

            Iterator operator++(int) {

                Iterator i = *this;
                ++*this;
                return i;
            }

            bool operator!=(const Iterator &iterator) {
                return currentNode != iterator.currentNode;
            }

            ListType operator*() {
                return currentNode->value;
            }

        private:
            const Node<ListType> *currentNode;
        };

        List() {}

        /**
         * @brief Append to the end of the list.
         * @param value
         */
        virtual void insert(ListType value) {

            _length++;

            if (head == nullptr) {

                head = new Node<ListType>(value);
                tail = head;
                return;
            }

            tail->next = new Node<ListType>(value);
            tail = tail->next;
        }

        /**
         * @brief Removes the first occurrence of the value specified.
         * @param value
         */
        virtual void remove(ListType value) {

            if (value == head->value) {

                head = head->next;
                return;
            }

            Node<ListType> *iter = head, *last = head;
            while (iter) {

                if (iter->value == value) {

                    // Remove node
                    last->next = iter->next;
                    delete iter; // De-allocate the node
                    _length--;
                    break;
                }

                last = iter;
                iter = iter->next;
            }
        }

        Node<ListType> *get_node(size_t index) {

            if (_length < index)
                return 0;

            Node<ListType> *iter = head;
            while (iter) {

                if (index == 0)
                    return iter;
                iter = iter->next;
                index--;
            }

            return 0; // This line is pretty irrelevant, it'd never run.
            // It's just to stop the IDE from telling me not all return paths are covered.

        }

        ListType get(size_t index) {
            return get_node(index)->value;
        }

        ListType operator[](size_t index) {
            return get(index);
        }

        size_t length() {
            return _length;
        }

        Iterator begin() {
            return Iterator(head);
        }

        Iterator end() {
            return Iterator(nullptr);
        }

        Node<ListType> *get_head() {
            return head;
        }

        Node<ListType> *get_tail() {
            return tail;
        }

        virtual void operator+=(ListType value) {
            insert(value);
        }

        virtual void operator-=(ListType value) {
            remove(value);
        }

        /**
         * @brief De-allocates all values, leaving a blank list.
         */
        void clear() {

            // De-allocate all nodes
            auto iter = head;
            while (iter) {

                auto temp = iter->next;
                delete iter;
                iter = temp;
            }
        }

        ~List() {
            clear();
        }

    protected:
        Node<ListType> *head = nullptr;
        Node<ListType> *tail = nullptr;
        size_t _length = 0;
    };

}

#endif
