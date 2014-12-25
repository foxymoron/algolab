#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>
#include <limits>
#include <algorithm>
#include <map>

using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef map<int, pii> mpi;

int main() {
    int t; cin >> t;

    for(int i=0; i<t; ++i) {
        int p; cin >> p;
        
        vi p_locations;
        p_locations.reserve(p);
        for(int j=0; j<p; ++j) {
            int x; cin >> x;
            p_locations.push_back(x);
        }

        sort(p_locations.begin(), p_locations.end());
        
        //mpi metrics;

  /*      for(int j=p_locations[0]; j<=p_locations[p - 1]; ++j) {
            int window_left = j - 100;
            int window_right = j + 100;
            int count = 0;
            int furthest = numeric_limits<int>::min();
            for(auto &pl:p_locations) {
                if(pl < window_left)
                    continue;
                if(pl >= window_left && pl <= window_right) {
                    count++;
                    if(abs(pl - j) > furthest)
                        furthest = abs(pl - j);
                }
                else if(pl > window_right)
                    break;
            }
            if(count > max_p)
                max_p = count;
            metrics[j] = make_pair(count, furthest);
        }
    */

        vector<pair<int, pii> > metrics; // center, count, distance

        int count = 1;
        vi::iterator left = p_locations.begin(), right = p_locations.begin();
        bool at_end = false;
        for(;;) {
            if(left == right) {
                vi::iterator duplicate = right;
                ++duplicate;
                if(duplicate == p_locations.end()) {
                    if(p_locations.size() != 1) {
                        metrics.push_back(make_pair(*left, make_pair(count, 0)));
                        break;
                    } else {
                        metrics.push_back(make_pair(*left, make_pair(count, 0)));
                        break;
                    }
                }
                else {
                    metrics.push_back(make_pair(*left, make_pair(count, 0)));
                    ++right;
                    count++;
                }
            }
            else if(abs(*left - *right) <= 200) {
                int center = (*left + *right) / 2;
                if(abs(*left - *right) % 2 == 0) {
                    metrics.push_back(make_pair(center, make_pair(count, center - *left)));
                } else {
                    metrics.push_back(make_pair(center, make_pair(count, max(center - *left, *right - center))));
                    if (center > 0)
                        metrics.push_back(make_pair(center + 1, make_pair(count, max(center + 1 - *left, *right - center - 1))));
                    else
                        metrics.push_back(make_pair(center - 1, make_pair(count, max(center - 1 - *left, *right - center + 1))));
                }
                if(!at_end) {
                    vi::iterator duplicate = right;
                    ++duplicate;
                    if(duplicate != p_locations.end()) {
                        ++right;
                        count++;
                    } else {
                        at_end = true;
                        ++left;
                        count--;
                    }
                } else {
                    ++left;
                    count--;
                }
            } else {
                // greater than 200
                ++left;
                count--;
            }
        }

/*        mpi fin;
        for(map<int, pii>::iterator it = metrics.begin(); it != metrics.end(); ++it) {
            if(it->second.first == max_p)
                fin[it->first] = it->second;
        }

        int min_d = numeric_limits<int>::max();
        for(map<int, pii>::iterator it = fin.begin(); it != fin.end(); ++it) {
            if(it->second.second < min_d)
                min_d = it->second.second;
        }

        cout << max_p << " " << min_d << endl;

        for(map<int, pii>::iterator it = fin.begin(); it != fin.end(); ++it) {
            if(it->second.first == max_p && it->second.second == min_d)
                cout << it->first << " ";
        }
        cout << endl; */
        int max_p = numeric_limits<int>::min();
        for(auto &m:metrics) {
            if(m.second.first > max_p)
                max_p = m.second.first;
        }

        int min_d = numeric_limits<int>::max();
        for(auto &m:metrics) {
            if(m.second.first == max_p) {
                if(m.second.second < min_d)
                    min_d = m.second.second;
            }
        }

        cout << max_p << " " << min_d << endl;

        vi locs;
        for(auto &m:metrics) {
            if(m.second.first == max_p && m.second.second == min_d)
                locs.push_back(m.first);
        }

        sort(locs.begin(), locs.end());

        //for(auto &l:locs)
        //    cout << l << " ";
        for(vi::iterator it = locs.begin(); it != locs.end(); ++it) {
            vi::iterator duplicate = it;
            ++duplicate;
            if(duplicate == locs.end())
                cout << *it;
            else
                cout << *it << " ";
        }
        cout << endl;

    }
    return 0;
}
