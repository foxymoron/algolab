#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

typedef vector<int> vi;
typedef vector< vector<int> > vvi;

void dfs(vvi &W, vi &V, vi &D, int d, int n) {
    V[n] = true;

    D[n] = d; // updated distance

    //cout << "DFS " << n << " " << D[n] << endl;
    for(auto &neighbor : W[n]) {
        if(!V[neighbor]) {
            dfs(W, V, D, d + 1, neighbor);
        }
    }
}

int main() {
    int t; cin >> t;

    for(int i=0; i<t; ++i) {
        int n; cin >> n;

        vvi W;
        vi V(n, false);
        vi D(n, 0);

        for(int j=0; j<n; ++j) {
            vi X;
            W.push_back(X);
        }

        for(int j=1; j<n; ++j) {
            int s, t; cin >> s >> t;
            W[s].push_back(t);
            W[t].push_back(s);
        }

        //for(int j=0; j<n; ++j) {
            //cout << j << ": ";
            //for(auto &neighbor:W[j]) {
                //cout << neighbor << " ";
            //}
            //cout << endl;
        //}

        dfs(W, V, D, 0, 0);
        auto max_index = distance(D.begin(), max_element(D.begin(), D.end()));

        //cout << max_index << endl << endl;
        fill(V.begin(), V.end(), false);
        fill(D.begin(), D.end(), 0);

        dfs(W, V, D, 0, max_index);

        cout << *max_element(D.begin(), D.end()) + 1 << endl;
    }
    return 0;
}
