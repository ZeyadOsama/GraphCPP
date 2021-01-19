//
// Created by zeyad-osama on 13/01/2020.
//

#include <graph/concrete/PseudoGraph.tpp>

#include <iostream>
#include <string>

using namespace std;
using namespace graph;

int main() {
    /*
     * Non Cyclic
     */

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

    cout << g.GetInfo() << endl;
    cout << "Graph 1::Is Cyclic: " << (g.IsCyclic() ? "True" : "False") << endl;

    /*
     * Cyclic
     */

    vector<string> nodes_names_cyc = {"A", "B", "C"};
    vector<int> nodes_data_cyc = {1, 2, 3};

    PseudoGraph<string, int> g_cyc;
    g_cyc.AddNode(nodes_names_cyc, nodes_data_cyc);
    for (int i = 0; i < nodes_names_cyc.size() - 1; i++) {
        g_cyc.AddEdge(nodes_names_cyc[i], nodes_names_cyc[i + 1]);
    }
    g_cyc.AddEdge(nodes_names_cyc[nodes_names_cyc.size() - 1], nodes_names_cyc[0]);


    cout << g_cyc.GetInfo() << endl;
    cout << "Graph 2::Is Cyclic: " << (g_cyc.IsCyclic() ? "True" : "False") << endl;

    cout << "\n------------------------------------" << endl;
    cout << "Done." << endl;
    cout << "------------------------------------" << endl;
}