# include "dijkstras.h"

int main(int argc, char** argv) {

    if (argc != 2) {
        cout << "Usage: ./dijkstras <filename>" << endl;
        return 1;
    }
    
    string filename = argv[1];
    Graph G;
    
    file_to_graph(filename, G);

    // for (auto item : G) { 
    //     for (auto it : item) {
    //         cout << it.src << " " << it.dst << " " << it.weight << endl;
    //     }
    // }
    // cout << endl;

    int start_vertex = 0;
    vector<int> previous(G.size(), -1);
    vector<int> distances = dijkstra_shortest_path(G, start_vertex, previous);
    for (size_t i = 0; i < G.size(); ++i) {
        vector<int> path = extract_shortest_path(distances, previous, i);
        print_path(path, distances[i]);
    }

    return 0;
}