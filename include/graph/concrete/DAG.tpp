//
// Created by zeyad-osama on 13/01/2020.
//

#ifndef LIB_GRAPH_DAG_GRAPH_TPP
#define LIB_GRAPH_DAG_GRAPH_TPP

#include <graph/interface/Graph.tpp>
#include <graph/concrete/PseudoGraph.tpp>

#include <vector>
#include <tuple>
#include <sstream>

namespace graph {

    template<typename T, typename K = T>
    class DAG : Graph<T, K> {
    public:
        using Graph<T, K>::AddNode;
        using Graph<T, K>::AddEdge;

    public:
        /**
         * @brief Constructor.
         */
        DAG();

        /**
         * @brief Copy Constructor
         */
        DAG(const DAG &G);

        /**
         * @brief Destructor.
         */
        ~DAG() override;

        /*
         * Trivial Functions
         */

        /**
         * @brief Add one node.
         */
        bool AddNode(T aName, K aData) override;

        /**
         * @brief Add edge from node A to node B.
         */
        bool AddEdge(T aSrc, T aDst, G_WEIGHT_TYPE aWeight = G_DEF_WEIGHT) override;

        /*
         * Core Functions
         */

        /**
         * @brief Returns a list of the names of neighbors.
         */
        std::vector<T> NeighborNames(T aNode) override;

        /**
         * @brief Returns a set of Nodes reachable from source node.
         */
        std::unordered_set<T>
        Explore(T aNode) override;

        /**
         * @brief Returns a list of Nodes that are reachable from the aNode.
         */
        std::vector<T>
        ReachableNames(T aNode) override;

        /**
         * @brief Returns true if there is a (directed) path from aSrc to aDst.
         */
        bool PathCheck(T aSrc, T aDst) override;

        /**
         * @brief Returns a list of all Nodes along with their Edges.
         */
        std::string GetInfo() override;

    private:
        PseudoGraph<T, K> mPseudoGraph;
    };

    template<typename T, typename K>
    DAG<T, K>::DAG() : mPseudoGraph(new PseudoGraph<T, K>(true)) {}

    template<typename T, typename K>
    DAG<T, K>::DAG(const DAG &G) {
        this->mPseudoGraph = G.mPseudoGraph;
    }

    template<typename T, typename K>
    DAG<T, K>::~DAG() = default;

    template<typename T, typename K>
    bool DAG<T, K>::AddNode(T aName, K aData) {
        return mPseudoGraph.AddNode(aName, aData);
    }

    template<typename T, typename K>
    bool DAG<T, K>::AddEdge(T aSrc, T aDst, double aWeight) {
        auto temp_pseudo_graph = this->mPseudoGraph;
        temp_pseudo_graph.AddEdge(aSrc, aDst, aWeight);
        if (temp_pseudo_graph.IsCyclic()) {
            std::cerr << "Adding this edge to the current graph will lead to internal cycles." << std::endl;
            return false;
        }
        return this->mPseudoGraph.AddEdge(aSrc, aDst);
    }

    template<typename T, typename K>
    std::vector<T> DAG<T, K>::NeighborNames(T aNode) {
        return this->mPseudoGraph.NeighborNames(aNode);
    }

    template<typename T, typename K>
    std::unordered_set<T> DAG<T, K>::Explore(T aNode) {
        return this->mPseudoGraph.Explore(aNode);
    }

    template<typename T, typename K>
    std::vector<T> DAG<T, K>::ReachableNames(T aNode) {
        return this->mPseudoGraph.ReachableNames(aNode);
    }

    template<typename T, typename K>
    bool DAG<T, K>::PathCheck(T aSrc, T aDst) {
        return this->mPseudoGraph.PathCheck(aSrc, aDst);
    }

    template<typename T, typename K>
    std::string DAG<T, K>::GetInfo() {
        return this->mPseudoGraph.GetInfo();
    }
} //namespace graph

#endif //LIB_GRAPH_DAG_GRAPH_TPP
