#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

typedef vector<int> vi;

int find_greatest_divisor(int x) {
    if(x == 2)
        return 1;

    int i;
    bool flag = false;
    for(i=2; i<=ceil(sqrt(x)); ++i) {
        if(x % i == 0) {
            flag = true;
            break;
        }
    }
    
    if(flag)
        return x/i;
    else
        return 1;
}

int main() {
    int t; cin >> t;

    vi greatest_divisors(10, -1);

    for(int i=0; i<t; ++i) {
        int n, c; cin >> n >> c;

        if(n > greatest_divisors.size()) {
            int size = n - greatest_divisors.size();
            for(int j=0; j<size; ++j) {
                greatest_divisors.push_back(-1);
            }
        }

        for(int j=0; j<c; ++j) {
            int x, y; cin >> x >> y;

            int hops = 0;
            while(x != y) {
                if(y > x) {
                    if(greatest_divisors[y] != -1) {
                        y = greatest_divisors[y];
                        hops++;
                    } else {
                        greatest_divisors[y] = find_greatest_divisor(y);
                        y = greatest_divisors[y];
                        hops++;
                    }
                } else {
                    if(greatest_divisors[x] != -1) {
                        x = greatest_divisors[x];
                        hops++;
                    } else {
                        greatest_divisors[x] = find_greatest_divisor(x);
                        x = greatest_divisors[x];
                        hops++;
                    }
                }
            }

            cout << hops << endl;
        }
    }
    return 0;
}
