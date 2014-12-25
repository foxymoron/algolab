#include <iostream>
#include <cmath>
#include <climits>

using namespace std;

int main() {
    int N;

    cin >> N;

    for(int i=0; i<N; ++i) {
        int l, m, n;
        cin >> l >> m >> n;

        int a, b, l_min = INT_MAX, b_max = -1;
        for(int k=n; k >= 0; --k) {
            for(int j=ceil(sqrt(l)); j >= 0; --j) {
                int l_remaining = l - (k * m + j * n);
                if(l_remaining >= 0 && l_remaining < l_min && j > b_max) {
                    l_min = l_remaining;
                    a = k;
                    b = j;
                }
            }
        }

        cout << a << " " << b << " " << l_min << " " << endl;
    }

    return 0;
}
