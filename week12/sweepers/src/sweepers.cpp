#include <iostream>
#include <vector>
#include <cmath>

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
        int n, m, s; cin >> n >> m >> s;

        vector<int> starting_locations(n, 0);
        vector<int> exit_rooms;
        for(int j=0; j<s; ++j) {
            int x, y; cin >> x >>  y;
            starting_locations[x]++;
            exit_rooms.push_back(y);
        }

        graph_t g(n);
        edge_capacity_map_t capacity = get(edge_capacity, g);
        reverse_edge_map_t rev_edge = get(edge_reverse, g);
        residual_capacity_map_t res_capacity = get(edge_residual_capacity, g);
        int src = add_vertex(g);
        int sink = add_vertex(g);

        // connect source to starting rooms with the 
        // number of sweepers starting at that room
        for(int j=0; j<n; ++j) {
            if(starting_locations[j] != 0)
                mf_add_edge(src, j, starting_locations[j], capacity, rev_edge, g);
        }

        // connect rooms with corridors
        vector<pair<int, int> > corridors;
        for(int j=0; j<m; ++j) {
            int x, y; cin >> x >> y;
            // save corridor
            corridors.push_back(make_pair(x, y));
            // add edge
            mf_add_edge(x, y, 1, capacity, rev_edge, g);
        }

        // connect rooms with doors outside to sink
        for(auto &r:exit_rooms) {
            mf_add_edge(r, sink, 1, capacity, rev_edge, g);
        }

        long flow = push_relabel_max_flow(g, src, sink);

        cout << flow << endl;

        for(auto &c:corridors) {
            edge_t e;
            tie(e, tuples::ignore) = edge(c.first, c.second, g);
            cout << source(e, g) << " " << target(e, g) << " " << res_capacity[e] <<  endl;
        }

        //if(flow != s) {
            //cout << "no" << endl;
            //continue;
        //} else {
            //bool ok = true;
            //for(auto &c:corridors) {
                //edge_t e;
                //tie(e, tuples::ignore) = edge(c.first, c.second, g);
                //cout << source(e, g) << " " << target(e, g) << " " << res_capacity[e] <<  endl;
                //if(res_capacity[e] > 0) {
                    //ok = false;
                    //break;
                //}
            //}
            //ok ? cout << "yes" : cout << "no";
            //cout << endl;
        //}
    }
    return 0;
}
