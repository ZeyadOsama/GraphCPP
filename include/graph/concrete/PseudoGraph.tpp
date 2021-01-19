//
// Created by zeyad-osama on 13/01/2020.
//

#ifndef LIB_GRAPH_PSEUDO_GRAPH_TPP
#define LIB_GRAPH_PSEUDO_GRAPH_TPP

#include <graph/interface/Graph.tpp>

#include <vector>
#include <tuple>
#include <sstream>

namespace graph {

template<typename T, typename K = T>
class PseudoGraph : Graph<T, K> {
public:
    using Graph<T, K>::AddNode;
    using Graph<T, K>::AddEdge;

public:
    /**
     * @brief Constructor.
     * Directed by default
     */
    PseudoGraph();

    /**
     * @brief Constructor.
     * @param[in] aDirected
     */
    explicit PseudoGraph(bool aDirected);

    /**
     * @brief Copy Constructor
     */
    PseudoGraph(const PseudoGraph &G);

    /**
     * @brief Destructor.
     */
    ~PseudoGraph() override;

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

    /**
     * @brief Deletes a given node.
     */
    bool DeleteNode(T aNode);

    /**
     * @brief Deletes a given edge.
     */
    bool DeleteEdge(T aSrc, T aDst, G_WEIGHT_TYPE aWeight = G_DEF_WEIGHT);

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
    void ExploreHelper(std::unordered_set<T> &aVisited, T aName);

private:
    bool mDirected = true;
};

template<typename T, typename K>
PseudoGraph<T, K>::PseudoGraph() = default;

template<typename T, typename K>
PseudoGraph<T, K>::PseudoGraph(bool aDirected) { this->mDirected = aDirected; }

template<typename T, typename K>
PseudoGraph<T, K>::PseudoGraph(const PseudoGraph &G) {
    this->mDirected = G.mDirected;

    /// Add all nodes in original to new PseudoGraph
    for (auto iter : G.mNodeMap) {
        int data = iter.second->GetData();
        std::string name = iter.first;

        auto *new_node = new Node<T, K>(name, data);
        this->mNodeMap.emplace(name, new_node);
    }

    /// Add all edges in original to new PseudoGraph
    std::vector<std::tuple<std::string, std::string, G_WEIGHT_TYPE> > edge_vec = G.GetEdges();
    for (auto edge : edge_vec) {
        std::string nodeA = std::get<0>(edge);
        std::string nodeB = std::get<1>(edge);
        G_WEIGHT_TYPE weight = std::get<2>(edge);

        this->AddEdge(nodeA, nodeB, weight);
    }
}

template<typename T, typename K>
PseudoGraph<T, K>::~PseudoGraph() {
    for (auto n : this->mNodeMap) {
        delete n.second;
    }
}

template<typename T, typename K>
bool PseudoGraph<T, K>::AddNode(T aName, K aData) {
    /// If node already exists, return false
    if (this->mNodeMap.find(aName) != this->mNodeMap.end()) {
        return false;
    }

    /// Else, dynamically Allocate a new Node and put it in mNodeMap
    auto *newNode = new Node<T, K>(aName, aData);
    this->mNodeMap.emplace(aName, newNode);
    return true;
}

template<typename T, typename K>
bool PseudoGraph<T, K>::AddEdge(T aSrc, T aDst, G_WEIGHT_TYPE aWeight) {
    /// If one of the nodes don't exist, return false
    if (this->mNodeMap.find(aSrc) == this->mNodeMap.end()) { return false; }
    if (this->mNodeMap.find(aDst) == this->mNodeMap.end()) { return false; }

    // Else add neighbor
    this->mNodeMap[aSrc]->AddNeighbor(aDst, aWeight);
    this->mNodeMap[aDst]->GetNeighborsSet().insert(aSrc);

    // If the PseudoGraph is undirected, also add the "Inverse-Edge"
    if (!this->mDirected) {
        this->mNodeMap[aDst]->AddNeighbor(aSrc, aWeight);
        this->mNodeMap[aSrc]->GetNeighborsSet().insert(aDst);
    }

    return true;
}

template<typename T, typename K>
bool PseudoGraph<T, K>::DeleteNode(T aNode) {
    /// If node does not exist, return false.
    if (this->mNodeMap.find(aNode) == this->mNodeMap.end()) {
        return false;
    }

    // For each Node N in {GetMapPtr()}, remove targetNode from N's {GetNeighborsMap()}
    // {GetNeighborsMap()} will have all Nodes that have an edge to aNode
    auto &set_reference = (this->mNodeMap[aNode]->GetNeighborsSet());
    for (auto iter : set_reference) {
        (this->mNodeMap[iter]->GetNeighborsMap())->erase(aNode);
    }

    // Remove targetNode from it's neighbors {GetNeighborsSet()}
    for (auto iter : *(this->mNodeMap[aNode]->GetNeighborsMap())) {
        this->mNodeMap[iter.first]->GetNeighborsSet().erase(aNode);
    }

    // Deallocate Node, remove it from {mNodeMap}
    delete this->mNodeMap[aNode];
    this->mNodeMap.erase(aNode);
    return true;
}

template<typename T, typename K>
bool PseudoGraph<T, K>::DeleteEdge(T aSrc, T aDst, G_WEIGHT_TYPE aWeight) {
    /// If one of the nodes don't exist or no such edge exists, return false.
    if (this->mNodeMap.find(aSrc) == this->mNodeMap.end()) { return false; }
    if (this->mNodeMap.find(aDst) == this->mNodeMap.end()) { return false; }

    std::unordered_map<std::string, std::multiset<G_WEIGHT_TYPE>> &neighbor_map_ref_1 =
            *(this->mNodeMap[aSrc]->GetNeighborsMap());

    if (neighbor_map_ref_1.find(aDst) == neighbor_map_ref_1.end()) { return false; }

    // Delete weight from multiset.
    std::multiset<G_WEIGHT_TYPE> &set_1 = neighbor_map_ref_1[aDst];
    set_1.erase(aWeight);

    // If that was the last edge from aSrc to aDst,
    // delete that (key, value) pair from {GetNeighborsMap()}.
    if (set_1.empty()) {
        neighbor_map_ref_1.erase(aDst);
    }

    // If the PseudoGraph is undirected,
    // also delete the "Inverse-Edge"
    if (!this->mDirected) {
        std::unordered_map<std::string, std::multiset<G_WEIGHT_TYPE>> &neighbor_map_ref_2 =
                *(this->mNodeMap[aDst]->GetNeighborsMap());

        // Delete weight from multiset
        std::multiset<G_WEIGHT_TYPE> &set_2 = neighbor_map_ref_2[aSrc];
        set_2.erase(aWeight);

        // If that was the last edge from aSrc to aDst,
        // delete that (key,value) pair from {GetNeighborsMap()}
        if (set_2.empty()) { neighbor_map_ref_2.erase(aSrc); }
    }

    return true;
}

template<typename T, typename K>
std::vector<T> PseudoGraph<T, K>::NeighborNames(T aNode) {
    if (this->mNodeMap.find(aNode) == this->mNodeMap.end()) { return std::vector<T>(); }

    std::vector<T> v;
    std::unordered_map<T, std::multiset<G_WEIGHT_TYPE>> *neighborMapPtr =
            this->mNodeMap[aNode]->GetNeighborsMap();
    for (auto it : *neighborMapPtr) { v.push_back(it.first); }

    return v;
}

template<typename T, typename K>
std::unordered_set<T> PseudoGraph<T, K>::Explore(T aNode) {
    if (this->mNodeMap.find(aNode) == this->mNodeMap.end()) { return std::unordered_set<T>(); }

    // Contains all nodes reachable from the passed Node
    std::unordered_set<T> reachable;
    this->ExploreHelper(reachable, aNode);
    return reachable;
}

template<typename T, typename K>
void PseudoGraph<T, K>::ExploreHelper(std::unordered_set<T> &aVisited, T aName) {
    aVisited.insert(aName);
    std::vector<T> neighbors = NeighborNames(aName);

    for (auto neighbor : neighbors) {
        if (aVisited.find(neighbor) == aVisited.end())
            this->ExploreHelper(aVisited, neighbor);
    }
}

template<typename T, typename K>
std::vector<T> PseudoGraph<T, K>::ReachableNames(T aNode) {
    std::vector<T> v;
    std::unordered_set<T> reachable = Explore(aNode);
    for (T name : reachable) {
        v.push_back(name);
    }
    return v;
}

template<typename T, typename K>
bool PseudoGraph<T, K>::PathCheck(T aSrc, T aDst) {
    std::unordered_set<T> reachable = Explore(aSrc);
    return (reachable.find(aDst) != reachable.end());
}

template<typename T, typename K>
std::string PseudoGraph<T, K>::GetInfo() {
    std::stringstream ss;
    // Prevents scientific-notation
    ss << std::fixed;
    ss << "\n\nPseudoGraph Info: " << std::endl;

    /// For Every Node
    for (auto itN : this->mNodeMap) {
        ss << "[" << itN.first << ": " << itN.second->GetData() << "] :\n";
        /// For Every Neighbor of Node
        for (auto itNN : *(itN.second->GetNeighborsMap())) {
            ss << "\t- (" << itNN.first << "): ";
            /// Print Each Edge of Neighbor
            for (auto weight : itNN.second) {
                ss << weight << "\n";
            }
        }
        ss << "\n";
    }
    return ss.str();
}
} //namespace graph

#endif //LIB_GRAPH_PSEUDO_GRAPH_TPP
