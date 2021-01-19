//
// Created by zeyad-osama on 13/01/2020.
//

#include <graph/concrete/DAG.tpp>

#include <iostream>
#include <string>

using namespace std;
using namespace graph;

int main() {
    vector<string> nodes_names = {"A", "B", "C"};
    vector<int> nodes_data = {1, 2, 3};

    DAG<string, int> g;
    g.AddNode(nodes_names, nodes_data);
    for (int i = 0; i < nodes_names.size() - 1; i++) {
        g.AddEdge(nodes_names[i], nodes_names[i + 1]);
    }
    g.AddEdge(nodes_names[nodes_names.size() - 1], nodes_names[0]);

    cout << g.GetInfo();

    g.AddEdge("A", "C");
    cout << g.GetInfo();

    cout << "\n------------------------------------" << endl;
    cout << "Done." << endl;
    cout << "------------------------------------" << endl;
}