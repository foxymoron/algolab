#include <iostream>
#include <vector>

using namespace std;

typedef vector<int> vi;
typedef vector< vector<int> > vvi;

int main() {
    int t; cin >> t;

    for(int i = 0; i < t; ++i) {
        int n; cin >> n;

        vvi mat;

        for(int j = 0; j < n; ++j) {
            vi X;
            for(int k = 0; k < n; ++k) {
                int a; cin >> a;
                X.push_back(a);
            }
            mat.push_back(X);
        }

        vvi partial_sums(n + 1, vi(n + 1, 0));

        for(int j = 1; j <= n; ++j) {
            for(int k = 1; k <= n; ++k) {
                partial_sums[j][k] = partial_sums[j-1][k-1] + 
                                     partial_sums[j-1][k] + 
                                     partial_sums[j][k-1] + 
                                     mat[j-1][k-1];
            }
        }

        int even_count = 0;
        for(int a = 0; a < n; ++a) { // loop for i1
            for(int b = 0; b < n; ++b) { // loop for i2
                for(int c = 0; c < n; ++c) { // loop for j1
                    for(int d = 0; d < n; ++d) { // loop for j2
                        if(b >= a && d >= c) {
                            //cout << a << " " << b << " " << c << " " << d << " ";
                            int sum = partial_sums[b + 1][d + 1] -
                                      partial_sums[b + 1][c] -
                                      partial_sums[a][d+1] +
                                      partial_sums[a][c];
                            //cout << sum << endl;
                            if(sum % 2 == 0)
                                even_count++;
                        }
                    }
                }
            }
        }

        cout << even_count << endl;
                        

    }

    return 0;
}
