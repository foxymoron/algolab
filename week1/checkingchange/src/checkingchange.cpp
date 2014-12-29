#include <iostream>
#include <vector>
#include <limits>

using namespace std;

typedef vector<int> vi;

int find_change(int t, vi & coins, vi & change) {
    if(change[t] != numeric_limits<int>::max())
        return change[t];
    else {
        int minimum = numeric_limits<int>::max();
        for(auto i:coins) {
            if(i <= t) {
                int temp = find_change(t - i, coins, change);
                if(temp != numeric_limits<int>::max())
                    minimum = min(minimum, 1 + find_change(t - i, coins, change));
            }
        }
        change[t] = minimum;
        return change[t];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;

    for(int i=0; i<t; ++i) {
        int c, m; cin >> c >> m;

        vi coins;
        for(int j=0; j<c; ++j) {
            int x; cin >> x;
            coins.push_back(x);
        }

        vi change(10000, numeric_limits<int>::max());
        change[0] = 0; // for the initial state
        for(int j=0; j<m; ++j) {
            int t; cin >> t;
            int answer = find_change(t, coins, change);

            if(answer != numeric_limits<int>::max())
                cout << answer << endl;
            else
                cout << "not possible" << endl;
        }

    }

    return 0;
}
