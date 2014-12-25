#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> number;
    number.push_back(0); // padding
    for(int i=0; i<n; ++i) {
        int bit;
        cin >> bit;
        number.push_back(bit);
    }

    vector<int> partial_sums;
    partial_sums.push_back(0);
    for(int i=1; i<=n; ++i) {
        partial_sums.push_back(partial_sums[i-1] + number[i]);
    }

    int even_pairs = 0;
    int even = 1; int odd = 0;
    for(int j=1; j<=n; ++j) {
        if(partial_sums[j] % 2 == 0) {
            even_pairs += even;
            even++;
        } else {
            even_pairs += odd;
            odd++;
        }
    }

    cout << even_pairs << endl;
    return 0;
}

