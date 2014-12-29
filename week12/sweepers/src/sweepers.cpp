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

        vector<int> starting_locations;
        vector<int> exit_locations;
        for(int j=0; j<s; ++j) {
            int x; cin >> x;
            starting_locations.push_back(x);
        }

        for(int j=0; j<s; ++j) {
            int x; cin >> x;
            exit_locations.push_back(x);
        }

        vector<vector<int> > corridors(n, vector<int> ());
        for(int j=0; j<m; ++j) {
            int x, y; cin >> x >> y;
            corridors[x].push_back(y);
        }

        graph_t g(n);
        edge_capacity_map_t capacity = get(edge_capacity, g);
        residual_capacity_map_t res_capacity = get(edge_residual_capacity, g);
        reverse_edge_map_t rev_edge = get(edge_reverse, g);
        int src = add_vertex(g);
        int sink = add_vertex(g);

        // connect source to starting locations
        for(int j=0; j<s; ++j)
            mf_add_edge(src, starting_locations[j], 1, capacity, rev_edge, g);

        // connect edges
        for(int j=0; j<n; ++j) {
            for(auto &e:corridors[j]) {
                mf_add_edge(j, e, 1, capacity, rev_edge, g);
                mf_add_edge(e, j, 1, capacity, rev_edge, g);
            }
        }

        // connect to exits to sink
        for(int j=0; j<s; ++j)
            mf_add_edge(exit_locations[j], sink, 1, capacity, rev_edge, g);

        long flow = push_relabel_max_flow(g, src, sink);

        if(flow != s) {
            cout << "no flow" << endl;
            cout << "no" << endl;
            continue;
        }

        // check for eulerian tour
        vector<int> out_degrees;
        auto vs = vertices(g);
        for(auto vit = vs.first; vit != vs.second; ++vit) {
            if(*vit != src && *vit != sink)
                out_degrees.push_back(out_degree(*vit, g));
        }

        auto es = edges(g);
        for(auto eit = es.first; eit != es.second; ++eit) {
            if(capacity[*eit] == 1 && res_capacity[*eit] == 0) {
                if(source(*eit, g) != src)
                    out_degrees[source(*eit, g)]--;
                if(target(*eit, g) != sink)
                    out_degrees[target(*eit, g)]--;
            }
        }

        bool is_eulerian = true;
        for(int j=0; j<n; ++j) {
            if((find(starting_locations.begin(), starting_locations.end(), j) == starting_locations.end()) &&
                (find(exit_locations.begin(), exit_locations.end(), j) == exit_locations.end()) &&
                    out_degrees[j] % 2 != 0)
                is_eulerian = false;
            if((find(starting_locations.begin(), starting_locations.end(), j) != starting_locations.end()) &&
                (find(exit_locations.begin(), exit_locations.end(), j) != exit_locations.end()) &&
                    out_degrees[j] % 2 == 0)
                is_eulerian = false;
        }

        if(!is_eulerian) {
            cout << "is not eulerian" << endl;
            cout << "no" << endl;
            continue;
        }

        cout << "yes" << endl;
    }

    return 0;
}
