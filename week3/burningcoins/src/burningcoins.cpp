#include <iostream>
#include <utility>
#include <vector>
#include <map>

using namespace std;

typedef vector<int> vi;

int find_optimal(int left, int right, bool has_turn, vector<vi> & cache, const vi & values, const int &n) {
    if(cache[left][right] != -1)
        return cache[left][right];

    if(has_turn) {
        // my turn
        if(left == right)
            cache[left][right] = values[left];
        else
            cache[left][right] = max(values[left] + find_optimal(left + 1, right, false, cache, values, n),
                                                        values[right] + find_optimal(left, right - 1, false, cache, values, n));
        return cache[left][right];
    } else {
        // bogey turn
        if(left == right)
            return 0;
        else
            return min(find_optimal(left + 1, right, true, cache, values, n),
                    find_optimal(left, right - 1, true, cache, values, n));
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;

    for(int i=0; i<t; ++i) {
        int n; cin >> n;

        vi values;
        for(int j=0; j<n; ++j) {
            int x; cin >> x;
            values.push_back(x);
        }

        if(n == 0) {
            cout << 0 << endl;
            continue;
        } else {
            vector<vi> cache(n, vi (n, -1));
            int best = find_optimal(0, n-1, true, cache, values, n);
            cout << best << endl;
        }
    }

    return 0;
}
