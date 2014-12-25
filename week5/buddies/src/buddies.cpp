#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS> graph_t;
typedef graph_traits<graph_t>::vertex_descriptor vertex_t;
const vertex_t NULL_VERTEX = graph_traits<graph_t>::null_vertex();

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;

    for(int i=0; i<t; ++i) {
        int n, c, f; cin >> n >> c >> f;
        
        graph_t g(n);
        vector<vector<string> > chars;
        for(int j=0; j<n; ++j) {
            vector<string> chars_st;
            for(int k=0; k<c; ++k) {
                string c; cin >> c;
                chars_st.push_back(c);
            }
            sort(chars_st.begin(), chars_st.end());
            chars.push_back(chars_st);
        }

        for(int j=0; j<n; ++j) {
            for(int k=j+1; k<n; ++k) {
                if(k == j)
                    continue;
                vector<string> chars_intersection;
                set_intersection(chars[j].begin(), chars[j].end(),
                                 chars[k].begin(), chars[k].end(),
                                 back_inserter(chars_intersection));
                if(chars_intersection.size() > f)
                    add_edge(j, k, g);
            }
        }

        vector<vertex_t> m(n);
        edmonds_maximum_cardinality_matching(g, &m[0]);

        bool flag = true;
        for(auto v:m) {
            if(v == NULL_VERTEX)
                flag = false;
        }

        if(flag)
            cout << "not optimal" << endl;
        else
            cout << "optimal" << endl;
    }
    return 0;
}
