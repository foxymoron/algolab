#include <iostream>
#include <vector>
#include <cmath>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/connected_components.hpp>
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
        int n, m, s; cin >> n >> m >> s;

        vector<int> starting_locations(n, 0);
        for(int j=0; j<s; ++j) {
            int x; cin >> x;
            starting_locations[x]++;
        }

        vector<int> exit_locations(n, 0);
        for(int j=0; j<s; ++j) {
            int x; cin >> x;
            exit_locations[x]++;
        }

        graph_t g(n);
        edge_capacity_map_t capacity = get(edge_capacity, g);
        reverse_edge_map_t rev_edge = get(edge_reverse, g);

        for(int j=0; j<m; ++j) {
            int x, y; cin >> x >> y;
            mf_add_edge(x, y, 1, capacity, rev_edge, g);
            mf_add_edge(y, x, 1, capacity, rev_edge, g);
        }

        bool is_eulerian = true;
        auto vs = vertices(g);
        for(auto vit = vs.first; vit != vs.second; ++vit) {
            int count = out_degree(*vit, g);
            if(starting_locations[*vit] > 0) count+=2;
            if(exit_locations[*vit] > 0) count+=2;
            count /= 2;
            if(count % 2 != 0) {
                is_eulerian = false;
                break;
            }
        }

        if(!is_eulerian) {
            cout << "no" << endl;
            continue;
        }

        int source = add_vertex(g);
        int sink = add_vertex(g);

        // connect source to entrances and exits to sink
        for(int j=0; j<n; ++j) {
            if(starting_locations[j] > 0)
                mf_add_edge(source, j, starting_locations[j], capacity, rev_edge, g);
        }

        for(int j=0; j<n; ++j) {
            if(exit_locations[j] > 0)
                mf_add_edge(j, sink, exit_locations[j], capacity, rev_edge, g);
        }

        long flow = push_relabel_max_flow(g, source, sink);

        if(flow == s)
            cout << "yes" << endl;
        else
            cout << "no" << endl;
    }

    return 0;
}
