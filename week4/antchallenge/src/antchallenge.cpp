#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <limits>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/tuple/tuple.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS,
        no_property, property<edge_weight_t, int> > graph_t;
typedef graph_traits<graph_t>::edge_descriptor edge_t;
typedef graph_traits<graph_t>::edge_descriptor vertex_t;

int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;

    for(int i=0; i<n; ++i) {
        int t, e, s, a, b; cin >> t >> e >> s >> a >> b;
        // t - no. of vertex
        // e - no. of edges
        // s - no. of species
        // a - starting tree
        // b - end tree

        graph_t g(t);
        property_map<graph_t, edge_weight_t>::type weight_map = get(edge_weight, g);
        
        map<edge_t, vector<int> > edge_weights;
        vector<pair<int, int> > graph_edges;

        for(int j=0; j<e; ++j) {
            int x, y; cin >> x >> y;

            edge_t edge;
            tie(edge, tuples::ignore) = add_edge(x, y, g);
            // save edge
            graph_edges.push_back(make_pair(x, y));

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
        for(int j=0; j<s; ++j) {
            vector<edge_t> st;
            for(auto &ew:edge_weights)
                weight_map[ew.first] = ew.second[j];
            kruskal_minimum_spanning_tree(g, back_inserter(st));
            spanning_trees.push_back(st);
        }

        graph_t g_prime(t);
        property_map<graph_t, edge_weight_t>::type weight_map_prime = get(edge_weight, g_prime);

        for(auto &ge:graph_edges) {
            edge_t edge;
            tie(edge, tuples::ignore) = add_edge(ge.first, ge.second, g_prime);
            weight_map_prime[edge] = numeric_limits<int>::max();
        }

        for(int j=0; j<s; ++j) {
            for(auto &ste:spanning_trees[j]) {
                if(edge_weights[ste][j] < weight_map_prime[ste])
                    weight_map_prime[ste] = edge_weights[ste][j];
            }
        }

        vector<vertex_t> predecessors(t);
        vector<int> distances(t);

        dijkstra_shortest_paths(g_prime, a, predecessor_map(&predecessors[0]).distance_map(&distances[0]));

        cout << distances[b] << endl;
    }

    return 0;
}
