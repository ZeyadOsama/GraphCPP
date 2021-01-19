//
// Created by zeyad-osama on 13/01/2020.
//

#include <graph/concrete/DAG.tpp>

#include <catch/catch.hpp>

using namespace std;
using namespace graph;

TEST_CASE("DAG Test", "[DAG],[Class]") {
    vector<string> nodes_names = {"A", "B", "C"};
    vector<int> nodes_data = {1, 2, 3};

    DAG<string, int> g;
    REQUIRE(g.AddNode(nodes_names, nodes_data) == true);
    for (int i = 0; i < nodes_names.size() - 1; i++) {
        REQUIRE(g.AddEdge(nodes_names[i], nodes_names[i + 1]) == true);
    }
    REQUIRE(g.AddEdge(nodes_names[nodes_names.size() - 1], nodes_names[0]) == false);
    REQUIRE(g.AddEdge("A", "C") == true);
}
