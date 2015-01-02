#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

using namespace boost;
using namespace std;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, property<edge_weight_t, int> > graph_t;
typedef graph_traits<graph_t>::edge_descriptor edge_t;
typedef graph_traits<graph_t>::vertex_descriptor vertex_t;

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    
    for(int i=0; i<t; ++i) {
        int t, e, s, a, b; cin >> t >> e >> s >> a >> b;

        graph_t g(t);
        property_map<graph_t, edge_weight_t>::type weight_map = get(edge_weight, g);

        map<edge_t, vector<int> > edge_weights;
        for(int j=0; j<e; ++j) {
            int x, y; cin >> x >> y;
            
            edge_t edge;
            tie(edge, tuples::ignore) = add_edge(x, y, g);

            vector<int> weights_species;
            for(int k=0; k<s; ++k) {
                int z; cin >> z;
                weights_species.push_back(z);
            }

            edge_weights[edge] = weights_species;
        }

        vector<int> hives;
        for(int j=0; j<s; ++j) {
            int x; cin >> x;
            hives.push_back(x);
        }

        vector<vector<edge_t> > spanning_trees;
        for(int j=0; j<s; ++j) { // for each species
            for(auto &ew:edge_weights)
                weight_map[ew.first] = ew.second[j];
            vector<edge_t> st;
            kruskal_minimum_spanning_tree(g, back_inserter(st));
            spanning_trees.push_back(st);
        }

        graph_t g_prime(t);
        property_map<graph_t, edge_weight_t>::type weight_map_prime = get(edge_weight, g_prime);

        for(int j=0; j<s; ++j) {
            for(auto &ste:spanning_trees[j]) {
                edge_t edge;
                tie(edge, tuples::ignore) = add_edge(source(ste, g), target(ste, g), g_prime);
                weight_map_prime[edge] = edge_weights[ste][j];
            }
        }

        vector<int> distances(t);
        dijkstra_shortest_paths(g_prime, a, distance_map(&distances[0]));

        cout << distances[b] << endl;
    }
    
    return 0;
}
