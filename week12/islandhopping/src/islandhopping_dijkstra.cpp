#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/tuple/tuple.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS, no_property, property<edge_weight_t, int> > graph_t;
typedef graph_traits<graph_t>::edge_descriptor edge_t;
typedef graph_traits<graph_t>::vertex_descriptor vertex_t;

int main() {
    int t; cin >> t;

    for(int i=0; i<t; ++i) {
        int k, r, e; cin >> k >> r >> e;

        vector<int> defences;
        defences.push_back(0); // for the first island
        for(int j=0; j<k-1; ++j) {
            int x; cin >> x;
            defences.push_back(x);
        }

        graph_t g(k+1);
        property_map<graph_t, edge_weight_t>::type weight_map = get(edge_weight, g);

        for(int j=0; j<k; ++j) {
            for(int l=1; l<=r; ++l) {
                if(j + l <= k) {
                    edge_t ed;
                    if(j >= k - r) {
                        tie(ed, tuples::ignore) = add_edge(j, k, g);
                        weight_map[ed] = 0;
                    } else {
                        tie(ed, tuples::ignore) = add_edge(j, j+l, g);
                        weight_map[ed] = defences[j+l];
                    }
                }
            }
        }

        vector<int> d(k+1);
        vector<int> p(k+1);

        dijkstra_shortest_paths(g, 0, predecessor_map(&p[0]).distance_map(&d[0]));

        if(e - d[p[k]] <= 0)
            cout << "safe" << endl;
        else {
            int hops = 0;
            int temp = p[k];
            while(temp != 0) {
                hops++;
                temp = p[temp];
            }
            cout << hops << " " << e - d[p[k]] << endl;
        }
    }
    return 0;
}
