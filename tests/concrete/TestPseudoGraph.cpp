//
// Created by zeyad-osama on 13/01/2020.
//

#include <graph/concrete/PseudoGraph.tpp>

#include <catch/catch.hpp>

using namespace std;
using namespace graph;

TEST_CASE("PseudoGraph Test - Not Directed", "[PseudoGraph],[Class],[Directed]") {
    vector<string> nodes_names = {"A", "B", "C", "D"};
    PseudoGraph<string, int> g(false);
    /// Add Nodes
    for (int i = 0; i < nodes_names.size(); i++) {
        REQUIRE(g.AddNode(pair<string, int>(nodes_names[i], i)) == true);
    }
    /// Add Edges
    for (int i = 0; i < nodes_names.size() - 1; i++) {
        REQUIRE(g.AddEdge(nodes_names[i], nodes_names[i + 1]) == true);
    }
    SECTION("NULL Exploration") {
        auto explored_nodes = g.Explore("E");
        REQUIRE(explored_nodes.empty());
    }

    SECTION("Normal Exploration - Start") {
        auto explored_nodes = g.Explore("A");
        REQUIRE(explored_nodes.size() == 4);
        for (auto &n : explored_nodes) {
            REQUIRE(std::count(nodes_names.begin(), nodes_names.end(), n));
        }
    }

    SECTION("Normal Exploration - End") {
        auto explored_nodes = g.Explore("D");
        REQUIRE(explored_nodes.size() == 4);
        for (auto &n : explored_nodes) {
            REQUIRE(std::count(nodes_names.begin(), nodes_names.end(), n));
        }
    }
}

TEST_CASE("PseudoGraph Test - Directed", "[PseudoGraph],[Class],[NotDirected]") {
    vector<string> nodes_names = {"A", "B", "C", "D"};
    PseudoGraph<string, int> g;
    /// Add Nodes
    for (int i = 0; i < nodes_names.size(); i++) {
        REQUIRE(g.AddNode(pair<string, int>(nodes_names[i], i)) == true);
    }
    /// Add Edges
    for (int i = 0; i < nodes_names.size() - 1; i++) {
        REQUIRE(g.AddEdge(nodes_names[i], nodes_names[i + 1]) == true);
    }

    SECTION("NULL Exploration") {
        auto explored_nodes = g.Explore("E");
        REQUIRE(explored_nodes.empty());
    }

    SECTION("Normal Exploration - Start") {
        auto explored_nodes = g.Explore("A");
        REQUIRE(explored_nodes.size() == 4);
        for (auto &n : explored_nodes) {
            REQUIRE(std::count(nodes_names.begin(), nodes_names.end(), n));
        }
    }

    SECTION("Normal Exploration - End") {
        auto explored_nodes = g.Explore("D");
        REQUIRE(explored_nodes.size() == 1);
        for (auto &n : explored_nodes) {
            REQUIRE(std::count(nodes_names.begin(), nodes_names.end(), n));
        }
    }
}

TEST_CASE("PseudoGraph Test - Node Addition", "[PseudoGraph],[NotDirected],[NodesAddition]") {
    vector<string> nodes_names = {"A", "B", "C", "D"};
    vector<int> nodes_data = {1, 2, 3, 4};

    SECTION("Templates T != K") {
        PseudoGraph<string, int> g;

        SECTION("Normal Node Addition") {
            for (int i = 0; i < nodes_names.size(); i++) {
                REQUIRE(g.AddNode(nodes_names[i], i) == true);
            }
        }

        SECTION("Pair Node Addition") {
            for (int i = 0; i < nodes_names.size(); i++) {
                REQUIRE(g.AddNode(pair<string, int>(nodes_names[i], i)) == true);
            }
        }

        SECTION("Vector Node Addition") {
            REQUIRE(g.AddNode(nodes_names, nodes_data) == true);
        }
    }

    SECTION("Templates T == K") {
        PseudoGraph<int, int> g;

        SECTION("Normal Node Addition") {
            for (int i = 0; i < nodes_names.size(); i++) {
                REQUIRE(g.AddNode(i, i) == true);
            }
        }

        SECTION("Pair Node Addition") {
            for (int i = 0; i < nodes_names.size(); i++) {
                REQUIRE(g.AddNode(pair<int, int>(i, i)) == true);
            }
        }

        SECTION("Vector Node Addition") {
            REQUIRE(g.AddNode(nodes_data) == true);
        }
    }
}

TEST_CASE("PseudoGraph Test - Edge Addition", "[PseudoGraph],[NotDirected],[EdgesAddition]") {
    vector<string> nodes_names = {"A", "B", "C", "D"};
    PseudoGraph<string, int> g(true);
    for (int i = 0; i < nodes_names.size(); i++) {
        REQUIRE(g.AddNode(nodes_names[i], i) == true);
    }

    SECTION("Normal Edge Addition") {
        for (int i = 0; i < nodes_names.size() - 1; i++) {
            REQUIRE(g.AddEdge(nodes_names[i], nodes_names[i + 1]) == true);
        }
    }

    SECTION("Weighted Edge Addition") {
        for (int i = 0; i < nodes_names.size() - 1; i++) {
            REQUIRE(g.AddEdge(nodes_names[i], nodes_names[i + 1], double(i)) == true);
        }
    }

    SECTION("Vector Edge Addition") {
        REQUIRE(g.AddEdge(nodes_names[0], nodes_names) == true);
    }

    SECTION("Vector To Vector Edge Addition") {
        REQUIRE(g.AddEdge(nodes_names, nodes_names) == true);
    }
}