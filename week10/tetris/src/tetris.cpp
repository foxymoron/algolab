#include <iostream>
#include <vector>
#include <utility>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> traits_t;
typedef adjacency_list<vecS, vecS, directedS, no_property,
        property<edge_capacity_t, long,
            property<edge_residual_capacity_t, long,
                property<edge_reverse_t, traits_t::edge_descriptor> > > > graph_t;
typedef property_map<graph_t, edge_capacity_t>::type edge_capacity_map_t;
typedef property_map<graph_t, edge_residual_capacity_t>::type residual_capacity_map_t;
typedef property_map<graph_t, edge_reverse_t>::type reverse_edge_map_t;
typedef graph_traits<graph_t>::vertex_descriptor vertex_t;
typedef graph_traits<graph_t>::edge_descriptor edge_t;

void mf_add_edge(int u, int v, long c, edge_capacity_map_t &capacity, 
        reverse_edge_map_t &rev_edge, graph_t &g) {
    edge_t e, reverse_edge;
    tie(e, tuples::ignore) = add_edge(u, v, g);
    tie(reverse_edge, tuples::ignore) = add_edge(v, u, g);
    capacity[e] = c;
    capacity[reverse_edge] = 0;
    rev_edge[e] = reverse_edge;
    rev_edge[reverse_edge] = e;
}

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;

    for(int i=0; i<t; ++i) {
        int w; cin >> w;

        graph_t g(w * 2);
        edge_capacity_map_t capacity = get(edge_capacity, g);
        reverse_edge_map_t rev_edge = get(edge_reverse, g);

        // edges for vertex capacities
        for(int j=1; j < (2 * w) - 2; j+=2) {
            //cout << j << " " << j + 1 << endl;
            mf_add_edge(j, j+1, 1, capacity, rev_edge, g);
        }

        int n; cin >> n;
        // edges for pieces
        for(int j=0; j<n; ++j) {
            int x, y; cin >> x >> y;
            int left = min(x, y);
            int right = max(x, y);
            if(left == right)
                continue;
            mf_add_edge(left * 2, (right * 2) - 1, 1, capacity, rev_edge, g);
        }

        long flow = push_relabel_max_flow(g, 0, (w * 2) - 1);

        cout << flow << endl;
    }

    return 0;
}
