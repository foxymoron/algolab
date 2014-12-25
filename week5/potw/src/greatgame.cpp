#include <iostream>
#include <vector>
#include <utility>
#include <limits>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;


int find_best_path(vvi &transitions, int cur_pos, bool is_best, const int &n, vector<pair<int, int> > &paths) {
    if(cur_pos == n)
        return 0;

    
    if(paths[cur_pos].first == -1 && is_best) {
        int minimum = numeric_limits<int>::max();
        for(auto &t:transitions[cur_pos])
            minimum = min(1 + find_best_path(transitions, t, false, n, paths), minimum);

        paths[cur_pos].first = minimum;
        return minimum;
    } else if(paths[cur_pos].second == -1 && !is_best) {
        int maximum = numeric_limits<int>::min();
        for(auto &t:transitions[cur_pos])
            maximum = max(1 + find_best_path(transitions, t, true, n, paths), maximum);

        paths[cur_pos].second = maximum;
        return maximum;
    } else {
        if(is_best)
            return paths[cur_pos].first;
        else
            return paths[cur_pos].second;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;

    for(int i=0; i<t; ++i) {
        int n, m; cin >> n >> m;
        int r, b; cin >> r >> b;
        r--; b--; // for 0-based indexing

        vvi transitions;
        for(int j=0; j<n; ++j) {
            vi temp;
            transitions.push_back(temp);
        }

        for(int j=0; j<m; ++j) {
            int u, v; cin >> u >> v;
            transitions[u-1].push_back(v - 1);
        }

        int red_best_dist, black_best_dist;

        vector<pair<int, int> > paths;
        for(int j=0; j<n; ++j)
            paths.push_back(make_pair(-1, -1));

        // find best path for Sherlock
        red_best_dist = find_best_path(transitions, r, true, n - 1, paths);
        // find best path for Moriarty
        black_best_dist = find_best_path(transitions, b, true, n - 1, paths);

        if(red_best_dist < black_best_dist)
            cout << 0 << endl;
        else if(red_best_dist == black_best_dist) {
            if(red_best_dist % 2 == 0)
                cout << 1 << endl;
            else
                cout << 0 << endl;
        } else
            cout << 1 << endl;
    }
    return 0;
}
