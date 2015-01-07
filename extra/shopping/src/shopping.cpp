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

        vector<int> shops(n, 0);
        for(int j=0; j<s; ++j) {
            int x; cin >> x;
            shops[x]++;
        }

        vector<vector<int> > streets(n, vector<int> ());
        for(int j=0; j<m; ++j) {
            int x, y; cin >> x >> y;
            streets[x].push_back(y);
        }

        graph_t g(n - 1);
        edge_capacity_map_t capacity = get(edge_capacity, g);
        reverse_edge_map_t rev_edge = get(edge_reverse, g);
        int source = add_vertex(g);
        int sink = add_vertex(g);

        // add edges from source to shops
        //for(int j=0; j<n; ++j) {
            //if(shops[j] > 0) {
                ////cout << source << " " << j - 1 << endl;
                //mf_add_edge(source, j - 1, shops[j], capacity, rev_edge, g);
            //}
        //}
        for(auto &s:streets[0]) {
                //cout << source << " " << s - 1 << endl;
                mf_add_edge(source, s - 1, 1, capacity, rev_edge, g);
        }

        // add reverse edge
        for(int j=1; j<n; ++j) {
            for(auto &s:streets[j]) {
                //cout << s - 1 << " " << j - 1 << endl;
                mf_add_edge(s - 1, j - 1, 1, capacity, rev_edge, g);
                //cout << j - 1 << " " << s - 1 << endl;
                mf_add_edge(j - 1, s - 1, 1, capacity, rev_edge, g);
            }
        }

        // add edge from intersections to sink
        //for(auto &s:streets[0]) {
            ////cout << s - 1 << " " << sink << endl;
            //mf_add_edge(s - 1, sink, 1, capacity, rev_edge, g);
        //}

        for(int j=0; j<n; ++j) {
            if(shops[j] > 0) {
                //cout << j - 1 << " " << sink << endl;
                mf_add_edge(j - 1, sink, shops[j], capacity, rev_edge, g);
            }
        }

        long flow = push_relabel_max_flow(g, source, sink);

        if(flow == s)
            cout << "yes" << endl;
        else
            cout << "no" << endl;
    }
    return 0;
}
