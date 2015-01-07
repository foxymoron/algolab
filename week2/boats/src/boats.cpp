#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool my_compare(const pair<int, int> & a, const pair<int, int> & b) {
    return a.second < b.second;
}

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;

    for(int i=0; i<t; ++i) {
        int n; cin >> n;

        vector<pair<int, int> > boats;
        for(int j=0; j<n; ++j) {
            int l, p; cin >> l >> p;
            boats.push_back(make_pair(l, p));
        }

        sort(boats.begin(), boats.end(), my_compare);

        vector<int> sol;
        // add the first boat
        sol.push_back(0);
        int right = boats[0].second;

        for(int j=1; j<n; ++j) {
            if(boats[j].second >= right) {
                sol.push_back(j);
                if(boats[j].second - right < boats[j].first)
                    right = boats[j].second + boats[j].first - (boats[j].second - right);
                else
                    right = boats[j].second;
            }
        }


        cout << sol.size() << endl;

    }


    return 0;
}
