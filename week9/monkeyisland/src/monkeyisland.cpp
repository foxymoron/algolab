#include <iostream>
#include <vector>
#include <limits>
#include <set>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/strong_components.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS> graph_t;
typedef graph_traits<graph_t>::edge_iterator edge_iterator_t;

int main() {
    int t; cin >> t;

    for(int i=0; i<t; ++i) {
        int n, m; cin >> n >> m;

        graph_t g(n);
        for(int j=0; j<m; ++j) {
            int x, y; cin >> x >> y;
            --x; --y; // zero indexing
            add_edge(x, y, g);
        }

        vector<int> costs;
        for(int j=0; j<n; ++j) {
            int x; cin >> x;
            costs.push_back(x);
        }

        vector<int> components(n);
        int num_components = strong_components(g, &components[0]);

        vector<int> components_min_cost(num_components, numeric_limits<int>::max());
        for(int j=0; j<n; ++j) {
            if(components_min_cost[components[j]] > costs[j])
                components_min_cost[components[j]] = costs[j];
        }

        if(num_components == 1) {
            cout << components_min_cost[0] << endl;
            continue;
        }
        
        edge_iterator_t ei, eend;
        vector<int> excluded_components;
        for(tie(ei, eend) = edges(g); ei != eend; ++ei) {
            if(components[source(*ei, g)] == components[target(*ei, g)])
                continue;
            else {
                excluded_components.push_back(components[target(*ei, g)]);
            }
        }
        
        int total_cost = 0;
        for(int j=0; j<num_components; ++j) {
            if(find(excluded_components.begin(), excluded_components.end(), j) ==
                    excluded_components.end())
                total_cost += components_min_cost[j];
        }

        cout << total_cost << endl;
    }
    return 0;
}
