#include <iostream>
#include <vector>
#include <map>
#include <limits>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

int take(vi m, map<vi, int> & cache, const vvi & stacks, const int & n) {
    // if memoized return
    if(cache.find(m) != cache.end())
        return cache[m];

    int maximum = 0;
    for(int i=1; i<(1<<n); ++i) {
        vi m_copy = m;
        int color = -1;
        int count = 0;
        for(int j=0; j<n; ++j) {
            if((i & (1<<j)) && m[j] != 0) {
                if(color == -1)
                    color = stacks[j][m[j] - 1];
                if(color != stacks[j][m[j] - 1]) {
                    count = 0;
                    break;
                }
                --m_copy[j];
                ++count;
            }
        }

        if(count != 0) {
            if(count < 2)
                maximum = max(maximum, take(m_copy, cache, stacks, n));
            else
                maximum = max(maximum, (1<<(count-2)) + take(m_copy, cache, stacks, n));
        }
        //for(auto &i:m)
            //cout << i << " ";
        //cout << endl;
        //cout << maximum << endl;
        //cout << "--------------------" << endl;

    }

    cache[m] = maximum;
    return cache[m];
}

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;

    for(int i=0; i<t; ++i) {
        int n; cin >> n;

        vi m;
        for(int j=0; j<n; ++j) {
            int x; cin >> x;
            m.push_back(x);
        }

        vvi stacks;
        for(int j=0; j<n; ++j) {
            vi stack;
            for(int k=0; k<m[j]; ++k) {
                int x; cin >> x;
                stack.push_back(x);
            }
            stacks.push_back(stack);
        }

        map<vi, int> cache;
        int best = take(m, cache, stacks, n);

        cout << best << endl;
    }


    return 0;
}
