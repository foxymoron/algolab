#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS,
        no_property, no_property> graph_t;

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;
    
    for(int i=0; i<t; ++i) {
        int n, m; cin >> n >> m;

        graph_t g(n + 1); // extra n vertices for the doors

        for(int j=0; j<m; ++j) {
            int s, t; cin >> s >> t;
            add_edge(s, t, g);
        }

        for(int j=0; j<n; ++j) {
            add_edge(j, 2 + n, g); // adding edge from v to v+n
                                 // from programmer to door
        }

        //cout << num_vertices(g) << endl;

        //cout << endl;

        //graph_traits<graph_t>::edge_iterator ei, ei_end;
        //for(tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) 
            //cout << source(*ei, g) << " " << target(*ei, g) << endl;

        //cout << endl;

        if(boyer_myrvold_planarity_test(g))
            cout << "yes" << endl;
        else
            cout << "no" << endl;

    }
    return 0;
}
