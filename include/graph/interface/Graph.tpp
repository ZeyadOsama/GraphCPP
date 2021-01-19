//
// Created by zeyad-osama on 13/01/2020.
//

#ifndef LIB_GRAPH_GRAPH_TPP
#define LIB_GRAPH_GRAPH_TPP

#include <graph/interface/Node.tpp>

namespace graph {

    template<typename T, typename K = T>
    class Graph {
    public:
        /**
         * @brief Constructor.
         */
        Graph();

        /**
         * @brief Destructor.
         */
        virtual ~Graph() = default;

        /*
         * Trivial Functions
         */

        /**
         * @brief Add one node.
         */
        virtual bool AddNode(T aName, K aData) = 0;

        /**
         * @brief Add one node.
         */
        bool AddNode(T aName);

        /**
         * @brief Given a pair of (T, K), insert pair as a Node
         */
        bool AddNode(std::pair<T, K> aNode);

        /**
         * @brief Given a vector of T, insert each T as a Node.
         */
        bool AddNode(std::vector<T> aNames);

        /**
         * @brief Given a names vector of T and a data vector K,
         * insert each T and K as a Node. Both vectors must be the same size.
         * Each name will be accompanied with the corresponding index in the data vector
         */
        bool AddNode(std::vector<T> aNames, std::vector<K> aData);

        /**
         * @brief Given a vector of (T, K) pairs, insert each pair as a Node
         */
        bool AddNode(std::vector<std::pair<T, K>> aNames);

        /**
         * @brief Add edge from node A to node B.
         */
        virtual bool AddEdge(T aSrc, T aDst, G_WEIGHT_TYPE aWeight = G_DEF_WEIGHT) = 0;

        /**
         * @brief Add edge from node A to std::vector<T> B.
         */
        bool AddEdge(T aSrc, std::vector<T> aDst);

        /**
         * @brief Add edge from std::vector<T> A to std::vector<T> B.
         */
        bool AddEdge(std::vector<T> aSrc, std::vector<T> aDst);

        /**
         * @brief Add Edge using a 3-tuple (node A,node B, weight).
         */
        bool AddEdge(std::tuple<T, T, G_WEIGHT_TYPE> aEdge);

        /*
         * Core Functions
         */

        /**
         * @brief Returns a list of the names of neighbors.
         */
        virtual std::vector<T> NeighborNames(T aNode) = 0;

        /**
         * @brief Returns a set of Nodes reachable from source node.
         */
        virtual std::unordered_set<T> Explore(T aNode) = 0;

        /**
         * @brief Returns a list of Nodes that are reachable from the aNode.
         */
        virtual std::vector<T> ReachableNames(T aNode) = 0;

        /**
         * @brief Returns true if there is a (directed) path from aSrc to aDst.
         */
        virtual bool PathCheck(T aSrc, T aDst) = 0;

        /**
         * @brief Returns a list of all Nodes along with their Edges.
         */
        virtual std::string GetInfo() = 0;

        /**
         * @brief Is the Node in the Graph
         */
        inline bool NodeExists(T aNode) const {
            return (this->mNodeMap.find(aNode) != this->mNodeMap.end());
        }

    protected:
        std::unordered_map<T, Node<T, K> *> mNodeMap;
    };

    template<typename T, typename K>
    bool Graph<T, K>::AddNode(T aName) {
        TEMPLATE_T_K_SAME_ASSERT(T, K);
        return this->AddNode(aName, aName);
    }

    template<typename T, typename K>
    bool Graph<T, K>::AddNode(std::pair<T, K> aNode) {
        return this->AddNode(aNode.first, aNode.second);
    }

    template<typename T, typename K>
    bool Graph<T, K>::AddNode(std::vector<T> aNames) {
        for (auto const &n : aNames) {
            this->AddNode(n);
        }
        return true;
    }

    template<typename T, typename K>
    bool Graph<T, K>::AddNode(std::vector<T> aNames, std::vector<K> aData) {
        if (aNames.size() != aData.size()) { return false; }
        for (int i = 0; i < aNames.size(); ++i) {
            this->AddNode(aNames[i], aData[i]);
        }
        return true;
    }

    template<typename T, typename K>
    bool Graph<T, K>::AddNode(std::vector<std::pair<T, K>> aNodes) {
        for (auto const &n : aNodes) {
            this->AddNode(n.first, n.second);
        }
        return true;
    }


    template<typename T, typename K>
    bool Graph<T, K>::AddEdge(T aSrc, std::vector<T> aDst) {
        for (auto const &n : aDst) {
            this->AddEdge(aSrc, n);
        }
        return true;
    }

    template<typename T, typename K>
    bool Graph<T, K>::AddEdge(std::vector<T> aSrc, std::vector<T> aDst) {
        for (auto &src : aSrc) {
            for (auto &dst : aDst) {
                this->AddEdge(src, dst);
            }
        }
        return true;
    }

    template<typename T, typename K>
    Graph<T, K>::Graph() { TEMPLATE_T_ASSERT(T); }

    template<typename T, typename K>
    bool Graph<T, K>::AddEdge(std::tuple<T, T, G_WEIGHT_TYPE> aEdge) {
        return this->AddEdge(std::get<0>(aEdge), std::get<1>(aEdge), std::get<2>(aEdge));
    }
} //namespace graph

#endif // LIB_GRAPH_GRAPH_TPP
