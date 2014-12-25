#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS> graph_t;
typedef vector<int> vi;
typedef vector< vector<int> > vvi;

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;

    for(int i = 0; i < t; ++i) {
        int m; cin >> m;

        vvi elections;

        for(int j = 0; j < m; ++j) {
            vi result;
            for(int k = 0; k < m - 1; ++k) {
                int r; cin >> r;
                result.push_back(r);
            }
            elections.push_back(result);
        }


        graph_t g(m);

        int T = 0;
        for(int j = 0; j < m - 1; ++j) {
            for(int k = 0; k < m; ++k) {
                add_edge(k, elections[k][j], g);
            }

            if(boyer_myrvold_planarity_test(g))
                T++;
            else
                break;
        }

        cout << T << endl;
    }
}
