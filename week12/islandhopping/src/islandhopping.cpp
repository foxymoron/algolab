#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <utility>
#include <map>
#include <limits>

using namespace std;

typedef pair<int, int> pii;
typedef pair<int, pair<int, int> > ppi;
typedef vector<int> vi;
typedef vector<pii> vpi;
typedef vector<ppi> vppi;
typedef map<ppi, vppi> mvpi;

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;

    for(int i=0; i<t; ++i) {
        int k, r, e; cin >> k >> r >> e;

        vi defences;
        defences.push_back(0);
        for(int j=0; j<k-1; ++j) {
            int x; cin >> x;
            defences.push_back(x);
        }

        mvpi graph;
        vppi leaves;

        queue<ppi> bfs; // index energy hops
        bfs.push(make_pair(0, make_pair(e, 0)));

        vppi temp;
        graph[make_pair(0, make_pair(e, 0))] = temp;

        while(!bfs.empty()) {
            ppi current = bfs.front();
            bfs.pop();

            if(current.first >= k - r) {
                leaves.push_back(current);
                continue;
            }
            
            if(current.second.first == 0 || current.second.first < 0)
                continue;

            for(int j=current.first + 1; j <= current.first + r; ++j) {
                if(j < k) {
                    bfs.push(make_pair(j, make_pair((current.second.first - defences[j]), current.second.second + 1)));
                    graph[current].push_back(make_pair(j, make_pair((current.second.first - defences[j]), current.second.second + 1)));
                    vppi temp;
                    graph[make_pair(j, make_pair((current.second.first - defences[j]), current.second.second + 1))] = temp;
                }
            }

        }
        
        int max_e = numeric_limits<int>::min();
        int min_hops = numeric_limits<int>::max();

        for(auto &l:leaves) {
            if(l.second.first > max_e)
                max_e = l.second.first;
        }

        if(max_e == 0 || max_e < 0) {
            cout << "safe" << endl;
        } else {
            for(auto &l:leaves) {
                if(l.second.first == max_e) {
                    if(min_hops > l.second.second)
                        min_hops = l.second.second;
                }
            }
            cout << min_hops << " " << max_e << endl;
        }

    }
    return 0;
}
