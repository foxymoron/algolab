#include <iostream>
#include <vector>

using namespace std;

typedef vector<long> vl;
typedef vector<vl> vvl;

long all_permutations(long current, vvl &counts, long hop, const int &k, const int &n) {
    if(hop == n - 1)
        return 1;

    if(counts[current][hop] != -1)
        return counts[current][hop];
    else {
        if(current == 0) {
            counts[current][hop] = all_permutations(current, counts, hop + 1, k, n) +
                all_permutations(current + 1, counts, hop + 1, k, n);
        } else if(current == k) {
            if(counts[0][hop] != -1)
                counts[current][hop] = counts[0][hop];
            else
                counts[current][hop] = all_permutations(current, counts, hop + 1, k, n) +
                    all_permutations(current - 1, counts, hop + 1, k, n);
        } else {
            counts[current][hop] = all_permutations(current, counts, hop + 1, k, n) +
                all_permutations(current - 1, counts, hop + 1, k, n) +
                all_permutations(current + 1, counts, hop + 1, k, n);
        }
        return counts[current][hop];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;

    for(int i=0; i<t; ++i) {
        int k, n; cin >> k >> n;
        k++;

        vvl counts(k, vl (n, -1));
        
        if(k == 1) {
            cout << 1 << endl;
            continue;
        }

        long total = 0;
        if(k % 2 == 0) {
            for(int j=0; j<k/2; ++j)
                total += all_permutations(j, counts, 0, k - 1, n);
            
            cout << (total * 2) % 100003 << endl;
        } else {
            long last;
            for(int j=0; j<k/2+1; ++j) {
                if(j == k/2)
                    last = all_permutations(j, counts, 0, k - 1, n);
                else
                    total += all_permutations(j, counts, 0, k - 1, n);
            }
            cout << ((total * 2) + last) % 100003 << endl;
        }

    }

    return 0;
}
