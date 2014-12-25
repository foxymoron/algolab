#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

typedef vector<int> vi;
typedef vector< vector<int> > vvi;
typedef pair<int, int> pii;

int main() {
    ios_base::sync_with_stdio(false);

    int t; cin >> t;

    for(int i=0; i<t; ++i) {
        int n, m; cin >> n >> m;
        int s, t; cin >> s >> t;
        s--; t--; // to start indexing at 0

        vvi W;
        vi V(n, 0);
        vi D(n, 0);

        for(int j=0; j<n; ++j) {
            vi X;
            W.push_back(X);
        }

        for(int j=0; j<m; ++j) {
            int src, tgt; cin >> src >> tgt;
            W[src - 1].push_back(tgt - 1);
        }

        queue<pii> bfs_queue;
        bfs_queue.push(make_pair(s, 0));
        V[s]++;

        bool done = false;
        int length;

        while(!bfs_queue.empty() && !done) {
            pii current = bfs_queue.front();
            bfs_queue.pop();

            for(auto &neighbor:W[current.first]) {
                if(V[neighbor] < 2) {
                    bfs_queue.push(make_pair(neighbor, current.second + 1));
                    V[neighbor]++;
                }
                if(V[neighbor] == 2 && neighbor == t) {
                    length = current.second + 1;
                    done = true;
                    break;
                }
            }
        }

        if(done)
            cout << length << endl;
        else
            cout << "no" << endl;
    }
    return 0;
}
