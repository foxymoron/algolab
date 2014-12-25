#include <iostream>
#include <vector>
#include <limits>
#include <numeric>

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
        int z, j; cin >> z >> j;

        vector<int> costs;
        for(int k=0; k<z; ++k) {
            int x; cin >> x;
            costs.push_back(x);
        }

        vector<int> rewards;
        for(int k=0; k<j; ++k) {
            int x; cin >> x;
            rewards.push_back(x);
        }

        vector<vector<int> > jobs_zone(z, vector<int> ());
        for(int k=0; k<j; ++k) {
            int n; cin >> n;
            for(int l=0; l<n; ++l) {
                int x; cin >> x;
                jobs_zone[x - 1].push_back(k);
            }
        }

        graph_t g(z + j);
        edge_capacity_map_t capacity = get(edge_capacity, g);
        reverse_edge_map_t rev_edge = get(edge_reverse, g);
        int source = add_vertex(g);
        int sink = add_vertex(g);

        for(int k=0; k<z; ++k) { // connect source to zones
            mf_add_edge(source, k, costs[k], capacity, rev_edge, g);
        }

        for(int k=0; k<z; ++k) { // connect zones to jobs
            for(auto &l:jobs_zone[k]) {
                mf_add_edge(k, z + l, numeric_limits<long>::max(), capacity, rev_edge, g);
            }
        }

        for(int k=0; k<j; ++k) { // jobs to sink
            mf_add_edge(z + k, sink, rewards[k], capacity, rev_edge, g);
        }

        int max_reward = accumulate(rewards.begin(), rewards.end(), 0);

        long flow = push_relabel_max_flow(g, source, sink);

        cout << max_reward - flow << endl;
    }

    return 0;
}
