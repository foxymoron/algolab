#include <iostream>
#include <limits>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/tuple/tuple.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS, no_property, property<edge_weight_t, int> > graph_t;
typedef graph_traits<graph_t>::edge_descriptor edge_t;

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;

    for(int i=0; i<t; ++i) {
        int n, m, s, t; cin >> n >> m >> s >> t;

        graph_t g(n * 4);
        property_map<graph_t, edge_weight_t>::type weight_map = get(edge_weight, g);

        for(int j=0; j<m; ++j) {
            int x, y, w; cin >> x >> y >> w;
            // if odd weight edge
            if(w % 2 != 0) {
                edge_t e;
                // even, even
                tie(e, tuples::ignore) = add_edge(x, (3 * n) + y, g);
                weight_map[e] = w;
                // even, odd
                tie(e, tuples::ignore) = add_edge(n + x, (2 * n) + y, g);
                weight_map[e] = w;
                // odd, even
                tie(e, tuples::ignore) = add_edge((2 * n) + x, n + y, g);
                weight_map[e] = w;
                // odd, odd
                tie(e, tuples::ignore) = add_edge((3 * n) + x, y, g);
                weight_map[e] = w;
            } else {
                edge_t e;
                // even, even
                tie(e, tuples::ignore) = add_edge(x, (2 * n) + y, g);
                weight_map[e] = w;
                // even, odd
                tie(e, tuples::ignore) = add_edge(n + x, (3 * n) + y, g);
                weight_map[e] = w;
                // odd, even
                tie(e, tuples::ignore) = add_edge((2 * n) + x, y, g);
                weight_map[e] = w;
                // odd, odd
                tie(e, tuples::ignore) = add_edge((3 * n) + x, n + y, g);
                weight_map[e] = w;
            }
        }

        vector<int> distances(n * 4);
        dijkstra_shortest_paths(g, s, distance_map(&distances[0]));

        if(distances[(3 * n) + t] < numeric_limits<int>::max())
            cout << distances[(3 * n) + t] << endl;
        else
            cout << "no" << endl;
    }

    return 0;
}
