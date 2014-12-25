#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    int cases;

    cin >> cases;

    for(int i=0; i<cases; ++i) {
        int m;
        double num;
        double sum = 0;

        cin >> m;

        for(int j=0; j<m; ++j) {
            cin >> num;
            sum += num;
        }
        
        cout << setprecision(9) << sum << endl;
    }


    return 0;
}
