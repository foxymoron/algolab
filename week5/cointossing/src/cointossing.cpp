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

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;

    for(int i=0; i<t; ++i) {
        int n, m; cin >> n >> m;

        graph_t g(m + n);
        edge_capacity_map_t capacity = get(edge_capacity, g);
        reverse_edge_map_t rev_edge = get(edge_reverse, g);
        //residual_capacity_map_t res_capacity = get(edge_residual_capacity, g);

        for(int j=0; j<m; ++j){
            int a, b, c; cin >> a >> b >> c;
            if(c == 1)
                mf_add_edge(j, a + m, 1, capacity, rev_edge, g);
            else if(c == 2)
                mf_add_edge(j, b + m, 1, capacity, rev_edge, g);
            else if(c == 0) {
                mf_add_edge(j, a + m, 1, capacity, rev_edge, g);
                mf_add_edge(j, b + m, 1, capacity, rev_edge, g);
            }
        }
        
        vertex_t source = add_vertex(g);
        vertex_t sink = add_vertex(g);
        
        for(int j=0; j<m; ++j)
            mf_add_edge(source, j, 1, capacity, rev_edge, g);

        long sum = 0;
        for(int j=0; j<n; ++j) {
            long x; cin >> x;
            sum += x;
            mf_add_edge(j + m, sink, x, capacity, rev_edge, g);
        }

        long flow = push_relabel_max_flow(g, source, sink);

        if(flow < sum || flow != m)
            cout << "no" << endl;
        else
            cout << "yes" << endl;

    }
    
    return 0;
}
