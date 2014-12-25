#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;
using namespace boost;

struct forest_edge {
    vector<int> weights;
    int fastest;
};

typedef adjacency_list<vecS, vecS, undirectedS,
        no_property, forest_edge> graph_t;
typedef graph_traits<graph_t>::vertex_descriptor vertex_t;
typedef graph_traits<graph_t>::edge_descriptor edge_t;

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;

    for(int i=0; i<t; ++i) {
        int n, m, s, a, b; cin >> n >> m >> s >> a >> b;
        // n - no. of trees
        // m - no. of edges
        // s - no. of species
        // a - start tree
        // b - end tree

        graph_t g(n);
        for(int j=0; j<m; ++j) {
            int u, v; cin >> u >> v;
            edge_t e;
            tie(e, tuples::ignore) = add_edge(u, v, g);
            for(int k=0; k<s; ++k) {
                int x; cin >> x;
                g[e].weights.push_back(x);
            }
        }
        
        map<int, vector<edge_t> > min_span_trees;
        for(int j=0; j<s; ++j) {
            vector<edge_t> span_tree;
            kruskal_minimum_spanning_tree(g, back_inserter(span_tree), weight_map(get(&forest_edge::weights[j], g)));
            min_span_trees[j] = span_tree;
        }

    }
    return 0;
}
