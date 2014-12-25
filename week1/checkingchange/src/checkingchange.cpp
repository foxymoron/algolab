#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

typedef vector<int> vi;

int main() {
    int currencies; cin >> currencies;

    for(int i=0; i<currencies; ++i) {
        int c, m; cin >> c >> m;

        vi coins;
        for(int j=0; j<c; ++j) {
            int coin;
            cin >> coin;
            coins.push_back(coin);
        }

        sort(coins.begin(), coins.end()); // not sure if the coins are
                                          // already sorted

        vi change(10, -1);
        for(int j=0; j<10; ++j) {
            for(vi::reverse_iterator ri = coins.rbegin(); ri != coins.rend(); ri++) {
                if(j - *ri > 0) {
                    if(j - *ri == 0) {
                        change[j] = 1;
                    } else {
                        change[j] = change[j - *ri] + 1;
                    }
                }
            }
        }

        for(auto &c : change) {
            cout << c << " ";
        }
        cout << "---" << i << endl;
    }

    return 0;
}
