#include <iostream>
#include <utility>
#include <map>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>

namespace boost {
    struct edge_component_t {
        enum { num = 555 };
        typedef edge_property_tag kind;
    } edge_component;
}

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, no_property,
                       property< edge_component_t, int> > graph_t;
typedef graph_traits<graph_t>::edge_descriptor edge_t;
typedef graph_traits<graph_t>::edge_iterator ei;

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;

    for(int i=0; i<t; ++i) {
        int n, m; cin >> n >> m;

        graph_t g;
        for(int j=0; j<m; ++j) {
            int u, v; cin >> u >> v;
            add_edge(u, v, g);
        }

        property_map<graph_t, edge_component_t>::type component = get(edge_component, g);
        biconnected_components(g, component);

        map<int, vector<edge_t> > count;
        ei ebeg, eend;
        for(tie(ebeg, eend) = edges(g); ebeg != eend; ++ebeg) {
            if(count[component[*ebeg]].size() == 0) {
                vector<edge_t> edges;
                edges.push_back(*ebeg);
                count[component[*ebeg]] = edges;
            } else {
                count[component[*ebeg]].push_back(*ebeg);
            }
        }

        vector< pair<int, int> > lex_edges;
        int num_critical = 0;
        for(int j=0; j<count.size(); ++j) {
            if(count[j].size() == 1)
                num_critical++;
        }
        cout << num_critical << endl;

        if(num_critical > 0) {
            for(int j=0; j<count.size(); ++j) {
                pair<int, int> vert_pair;
                if(count[j].size() == 1) {
                    if(source(count[j][0], g) > target(count[j][0], g))
                        vert_pair = make_pair(target(count[j][0], g), source(count[j][0], g));
                    else
                        vert_pair = make_pair(source(count[j][0], g), target(count[j][0], g));

                    lex_edges.push_back(vert_pair);
                }
            }

            sort(lex_edges.begin(), lex_edges.end());
            for(auto &verts:lex_edges) {
                cout << verts.first << " " << verts.second << endl;
            }
        }
    }
    return 0;
}
