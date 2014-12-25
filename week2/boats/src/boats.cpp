#include <iostream>
#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef vector< pair<int, int> > vpi;

bool pair_sort(pair<int, int> a, pair<int, int> b) { return a.first < b.first; }

int main() {
    int t; cin >> t;

    for(int i = 0; i < t; ++i) {
        int N; cin >> N;

        vi boat_length(N);
        vpi boat_ring;

        for(int i = 0; i < N; ++i) {
            int l, p; cin >> l >> p;
            boat_length[i] = l;
            boat_ring.push_back(make_pair(p, i));
        }

        sort(boat_ring.begin(), boat_ring.end(), pair_sort);

        for(auto &boat : boat_ring) {
            cout << boat.first << " " << boat.second << endl;
        }
    }
    return 0;
}
