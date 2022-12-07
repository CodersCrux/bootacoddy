#ifndef BOOTACODDY_UTIL_DATA_NODE_HPP
#define BOOTACODDY_UTIL_DATA_NODE_HPP

#include "../../util/types.h"

namespace bac::types {

    template<typename NodeType>
    struct Node {

        Node(NodeType value, Node<NodeType> *next = nullptr)
                : value(value), next(next) {}

        Node *next;
        NodeType value;
    };

}

#endif