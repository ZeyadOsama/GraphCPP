//
// Created by zeyad-osama on 13/01/2020.
//

#ifndef LIB_GRAPH_NODE_HPP
#define LIB_GRAPH_NODE_HPP

#include <graph/helpers/assertions.h>

#include <string>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <utility>

#define G_WEIGHT_TYPE     double
#define G_DEF_WEIGHT      1

namespace graph {

    template<typename T, typename K = T>
    class Node {
    public:
        Node(T aName, K aData);

        ~Node();

        void AddNeighbor(T aNeighborName, G_WEIGHT_TYPE aWeight);

        inline K GetData() {
            return this->mData;
        }

        inline std::unordered_map<T, std::multiset<G_WEIGHT_TYPE>> *GetNeighborsMap() const {
            return this->mNeighborsMap;
        }

        inline std::unordered_set<T> GetNeighborsSet() const {
            return this->mNeighborsSet;
        }

    private:
        T mName;
        K mData;
        /// List of Nodes that this node has an edge to
        /// [THIS NODE] => [NEIGHBOR NODE 1], [NEIGHBOR NODE 2], [NEIGHBOR NODE N]
        std::unordered_map<T, std::multiset<G_WEIGHT_TYPE>> *mNeighborsMap;
        /// List of Nodes that have an edge to this Node
        /// [NEIGHBOR NODE 1], [NEIGHBOR NODE 2], [NEIGHBOR NODE N] => [THIS NODE]
        std::unordered_set<T> mNeighborsSet;
    };

    template<typename T, typename K>
    Node<T, K>::Node(T aName, K aData)
            : mData(aData), mName(aName) {
        TEMPLATE_T_ASSERT(T);
        this->mNeighborsMap = new std::unordered_map<T, std::multiset<G_WEIGHT_TYPE>>();
    }

    template<typename T, typename K>
    Node<T, K>::~Node() {
        delete this->mNeighborsMap;
    }

    template<typename T, typename K>
    void Node<T, K>::AddNeighbor(T aNeighborName, G_WEIGHT_TYPE aWeight) {
        // If the new neighbor is not already a neighbor add it to the list
        if (this->mNeighborsMap->find(aNeighborName) == this->mNeighborsMap->end()) {
            std::multiset<G_WEIGHT_TYPE> tempSet;
            std::pair<T, std::multiset<G_WEIGHT_TYPE>> temp_pair(aNeighborName, tempSet);
            this->mNeighborsMap->insert(temp_pair);
        }
        // Add edge of this weight
        (*this->mNeighborsMap)[aNeighborName].insert(aWeight);
    }
} //namespace graph

#endif // LIB_GRAPH_NODE_HPP
