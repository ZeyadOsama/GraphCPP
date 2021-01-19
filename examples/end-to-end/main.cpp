//
// Created by zeyad-osama on 13/01/2020.
//

#include <graph/concrete/PseudoGraph.tpp>

#include <iostream>
#include <string>

using namespace std;
using namespace graph;

int main() {
    vector<string> nodes_names = {"A", "B", "C", "D"};
    vector<int> nodes_data = {1, 2, 3, 4};

    PseudoGraph<string, int> g;
    g.AddNode(nodes_names, nodes_data);
    for (int i = 0; i < nodes_names.size() - 1; i++) {
        g.AddEdge(nodes_names[i], nodes_names[i + 1]);
    }

    auto explored_nodes = g.Explore("A");
    for (auto const &n : explored_nodes) {
        cout << n << endl;
    }

    cout << g.GetInfo();

    cout << "\n------------------------------------" << endl;
    cout << "Done." << endl;
    cout << "------------------------------------" << endl;
}