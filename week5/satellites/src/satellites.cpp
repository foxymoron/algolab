#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS> graph_t;
typedef graph_traits<graph_t>::vertex_descriptor vertex_t;
typedef graph_traits<graph_t>::out_edge_iterator out_edge_it;
const vertex_t NULL_VERTEX = graph_traits<graph_t>::null_vertex();

void DFS(int u, graph_t &g, vector<bool> &v, vector<vertex_t> &m) {
    v[u] = true;

    out_edge_it ei, eend;
    for(tie(ei, eend) = out_edges(u, g); ei != eend; ++ei) {
        const int t = target(*ei, g);
        if(m[u] != t && !v[t])
            DFS(t, g, v, m);
        else if(m[u] == t && !v[t])
            DFS(t, g, v, m);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;

    for(int i=0; i<t; ++i) {
        int g, s, l; cin >> g >> s >> l;

        graph_t gr(g+s);
        for(int j=0; j<l; ++j) {
            int u, v; cin >> u >> v;
            add_edge(u, g+v, gr);
        }

        vector<vertex_t> m(g+s);
        vector<bool> v(g+s, false);
        vector<vertex_t> sp;
        edmonds_maximum_cardinality_matching(gr, &m[0]);

        for(int j=0; j<g; ++j) {
            if(m[j] == NULL_VERTEX)
                sp.push_back(j);
        }

        for(auto &u:sp)
            DFS(u, gr, v, m);

        vector<vertex_t> g_prime, s_prime;
        for(int j=0; j<g+s; ++j) {
            if(j < g && !v[j])
                g_prime.push_back(j);
            else if(j >= g && v[j])
                s_prime.push_back(j);
        }

        cout << g_prime.size() << " " << s_prime.size() << endl;
        for(auto &u:g_prime)
            cout << u << " ";
        for(auto &u:s_prime)
            cout << u - g << " ";
        cout << endl;

    }
    return 0;
}
