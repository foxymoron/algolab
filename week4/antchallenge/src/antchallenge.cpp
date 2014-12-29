#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/tuple/tuple.hpp>

using namespace std;
using namespace boost;

struct forest_edge {
    vector<int> weights;
};

typedef adjacency_list<vecS, vecS, undirectedS,
        no_property, forest_edge> graph_t;
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

        for(int j=0; j<e; ++j) {
            int x, y; cin >> x >> y;

            edge_t edge;
            tie(edge, tuples::ignore) = add_edge(x, y, g);

            vector<int> weights_species;
            for(int k=0; k<s; ++k) {
                int z; cin >> z;
                weights_species.push_back(z);
            }

            g[edge].weights = weights_species;
        }

        vector<int> hives;
        for(int j=0; j<s; ++j) {
            int x; cin >> x;
            hives.push_back(x);
        }

        vector<vector<edge_t> > spanning_trees;
        for(int j=0; j<s; ++j) {
            vector<edge_t> st;
            auto w_map = get(&forest_edge::weights, g);

            kruskal_minimum_spanning_tree(g, back_inserter(st),
                    weight_map(w_map));
            spanning_trees.push_back(st);
        }
    }

    return 0;
}
