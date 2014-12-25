#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/tuple/tuple.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS,
        no_property,
        property<edge_weight_t, int> > Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
typedef property_map<Graph, edge_weight_t>::type WeightMap;

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;

    for(int i=0; i<t; ++i) {
        int n, m; cin >> n >> m;

        Graph G(n);
        WeightMap wm = get(edge_weight, G);

        for(int j=0; j<m; ++j) {
            int s, t, w; cin >> s >> t >> w;
            Edge e;
            tie(e, tuples::ignore) = add_edge(s, t, G);
            wm[e] = w;
        }

        vector<Edge> spanning_tree;
        kruskal_minimum_spanning_tree(G, back_inserter(spanning_tree));

        int sum = 0; // spanning tree edge weight sum
        for(auto &e:spanning_tree)
            sum += wm[e];

        vector<int> dist(num_vertices(G));
        dijkstra_shortest_paths(G, 0, distance_map(&dist[0]));

        int max_dist = 0;
        for(auto &d:dist) {
            if(d > max_dist)
                max_dist = d;
        }

        cout << sum << " " << max_dist << endl;
    }
    return 0;
}
