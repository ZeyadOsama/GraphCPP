//
// Created by zeyad-osama on 13/01/2020.
//

#ifndef LIB_GRAPH_EXECUTION_GRAPH_TPP
#define LIB_GRAPH_EXECUTION_GRAPH_TPP

#include <graph/interface//Graph.tpp>
#include <graph/concrete/DAG.tpp>

namespace graph {

    template<typename T, typename K = T>
    class ExecutionGraph : Graph<T, K> {
    public:
        using Graph<T, K>::AddNode;
        using Graph<T, K>::AddEdge;

    public:
        /**
         * @brief Constructor.
         */
        ExecutionGraph();

        /**
         * @brief Copy Constructor
         */
        ExecutionGraph(const ExecutionGraph &G);

        /**
         * @brief Destructor.
         */
        ~ExecutionGraph() override;

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
        DAG<T, K> mInternalGraph;
    };
} //namespace graph

#endif //LIB_GRAPH_EXECUTION_GRAPH_TPP
