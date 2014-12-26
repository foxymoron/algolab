#include <iostream>
#include <vector>

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

int main(int argc, char *argv[])
{
    ios_base::sync_with_stdio(false);
    int t; cin >> t;

    for (int i = 0; i < t; ++i) {
        int n, m, k, l; cin >> n >> m >> k >> l;

        vector<int> police_stations(n, 0);
        for(int j=0; j<k; ++j) {
            int x; cin >> x;
            police_stations[x]++;
        }

        vector<int> photo_locations(n, 0);
        for(int j=0; j<l; ++j) {
            int x; cin >> x;
            photo_locations[x]++;
        }

        vector<vector<int> > roads(n, vector<int> ());
        for(int j=0; j<m; ++j) {
            int x, y; cin >> x >> y;
            roads[x].push_back(y);
        }

        graph_t g(2 * n);
        edge_capacity_map_t capacity = get(edge_capacity, g);
        reverse_edge_map_t rev_edge = get(edge_reverse, g);

        vertex_t source = add_vertex(g);
        vertex_t sink = add_vertex(g);

        // connect source to police stations
        for(int j=0; j<n; ++j) {
            if(police_stations[j] != 0)
                mf_add_edge(source, j, police_stations[j], capacity, rev_edge, g);
        }

        // a bobby can move through multiple roads and police stations
        // when not carrying a photo
        for(int j=0; j<n; ++j) {
            for(auto &r:roads[j])
                mf_add_edge(j, r, numeric_limits<long>::max(), capacity, rev_edge, g);
        }

        // connect intersections with photo locations to photo location vertices
        for(int j=0; j<n; ++j) {
            if(photo_locations[j] != 0)
                mf_add_edge(j, n + j, photo_locations[j], capacity, rev_edge, g);
        }

        // only one bobby can go through a street carrying a photo
        for(int j=0; j<n; ++j) {
            for(auto &r:roads[j])
                mf_add_edge(n + j, n + r, 1, capacity, rev_edge, g);
        }

        // connect exit police stations
        for(int j=0; j<n; ++j) {
            if(police_stations[j] != 0)
                mf_add_edge(n + j, sink, police_stations[j], capacity, rev_edge, g);
        }

        long flow = push_relabel_max_flow(g, source, sink);

        cout << flow << endl;
    }
    return 0;
}
