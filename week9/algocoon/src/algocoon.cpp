#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <limits>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/tuple/tuple.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS> traits_t;
typedef adjacency_list<vecS, vecS, directedS, no_property,
        property<edge_capacity_t, long,
            property<edge_residual_capacity_t, long,
                property<edge_reverse_t, traits_t::edge_descriptor> > > > graph_t;
typedef property_map<graph_t, edge_capacity_t>::type edge_capacity_map_t;
typedef property_map<graph_t, edge_residual_capacity_t>::type residual_capacity_map_t;
typedef property_map<graph_t, edge_reverse_t>::type reverse_edge_map_t;
typedef graph_traits<graph_t>::vertex_descriptor vertex_t;
typedef graph_traits<graph_t>::edge_descriptor edge_t;
typedef graph_traits<graph_t>::out_edge_iterator out_edge_iterator_t;

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

    srand(time(0));

    for(int i=0; i<t; ++i) {
        int n, m; cin >> n >> m;

        graph_t g(n);
        edge_capacity_map_t capacity = get(edge_capacity, g);
        reverse_edge_map_t rev_edge = get(edge_reverse, g);
        residual_capacity_map_t res_capacity = get(edge_residual_capacity, g);
        
        for(int j=0; j<m; ++j) {
            int a, b, c; cin >> a >> b >> c;
            mf_add_edge(a, b, c, capacity, rev_edge, g);
        }

        long minimum_flow = numeric_limits<long>::max();
        int best_source, best_sink;
        int v  = rand() % n;
        for(int i=0; i<n; ++i) {
            if(i != v) {
                long flow = push_relabel_max_flow(g, v, i);
                if(flow < minimum_flow) {
                    minimum_flow = flow;
                    best_source = v;
                    best_sink = i;
                }
            }
        }
        
        for(int i=0; i<n; ++i) {
            if(i != v) {
                long flow = push_relabel_max_flow(g, i, v);
                if(flow < minimum_flow) {
                    minimum_flow = flow;
                    best_source = i;
                    best_sink = v;
                }
            }
        }

        //cout << best_source << " " << best_sink << endl;

        minimum_flow = push_relabel_max_flow(g, best_source, best_sink);

        std::queue<int> bfs_queue;
        vector<bool> visited(n, false);
        bfs_queue.push(best_source);
        visited[best_source] = true;

        vector<int> sculptures;

        while(!bfs_queue.empty()) {
            int current = bfs_queue.front();
            bfs_queue.pop();

            sculptures.push_back(current);

            out_edge_iterator_t edge_i, edge_end;
            for(tie(edge_i, edge_end) = out_edges(current, g); edge_i != edge_end; ++edge_i) {
                if(res_capacity[*edge_i] > 0) {
                    if(!visited[target(*edge_i, g)]) {
                        bfs_queue.push(target(*edge_i, g));
                        visited[target(*edge_i, g)] = true;
                    }
                }
            }
        }

        cout << minimum_flow << endl;
        for(auto &s:sculptures)
            cout << s << " ";
        cout << endl;
    }
    return 0;
}
