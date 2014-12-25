#include <iostream>
#include <deque>
#include <utility>
#include <vector>
#include <map>

using namespace std;

typedef deque<int> di;

int find_optimal(bool has_turn, map<di, pair<int, int> > & optimal_values, di values, const int &n) {
    if(has_turn && optimal_values.find(values) == optimal_values.end()) {
        if(values.size() > 1) {
            di copy1(values), copy2(values);
            copy1.pop_front();
            copy2.pop_back();
            optimal_values[values] = make_pair(max(values.front() + find_optimal(false, optimal_values, copy1, n),
                    values.back() + find_optimal(false, optimal_values, copy2, n)), -1);
            return optimal_values[values].first;
        } else {
            optimal_values[values] = make_pair(values.front(), -1);
            return optimal_values[values].first;
        }
    } else if(!has_turn && optimal_values.find(values) == optimal_values.end()) {
        if(values.size() > 1) {
            di copy1(values), copy2(values);
            copy1.pop_front();
            copy2.pop_back();
            optimal_values[values] = make_pair(-1, min(find_optimal(true, optimal_values, copy1, n),
                    find_optimal(true, optimal_values, copy2, n)));
            return optimal_values[values].second;
        } else {
            optimal_values[values] = make_pair(-1, 0);
            return 0;
        }
    } else {
        if(has_turn && optimal_values[values].first != -1)
            return optimal_values[values].first;
        else if(has_turn && optimal_values[values].first == -1) {
            if(values.size() > 1) {
                di copy1(values), copy2(values);
                copy1.pop_front();
                copy2.pop_back();
                optimal_values[values] = make_pair(max(values.front() + find_optimal(false, optimal_values, copy1, n),
                        values.back() + find_optimal(false, optimal_values, copy2, n)), -1);
                return optimal_values[values].first;
            } else {
                optimal_values[values] = make_pair(values.front(), -1);
                return optimal_values[values].first;
            }
        } else if(!has_turn && optimal_values[values].second != -1)
            return optimal_values[values].second;
        else if(!has_turn && optimal_values[values].second == -1) {
            if(values.size() > 1) {
                di copy1(values), copy2(values);
                copy1.pop_front();
                copy2.pop_back();
                optimal_values[values] = make_pair(-1, min(find_optimal(true, optimal_values, copy1, n),
                        find_optimal(true, optimal_values, copy2, n)));
                return optimal_values[values].second;
            } else {
                optimal_values[values] = make_pair(-1, 0);
                return 0;
            }
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;

    for(int i=0; i<t; ++i) {
        int n; cin >> n;

        di values;
        for(int j=0; j<n; ++j) {
            int x; cin >> x;
            values.push_back(x);
        }

        if(n == 0) {
            cout << 0 << endl;
            continue;
        } else {
            map<di, pair<int, int>> optimal_values;
            int best = find_optimal(true, optimal_values, values, n);
            cout << best << endl;
        }
    }

    return 0;
}
