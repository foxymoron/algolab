#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <map>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef map<int, int> mii;

bool has_all(vi &t, int n) {
    bool ret = true;

    for(int i=0; i<n; ++i) {
        auto res = find(t.begin(), t.end(), i);
        if(res == t.end()) {
            ret = false;
            break;
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;

    for(int i=0; i<t; ++i) {
        int n; cin  >> n;

        vi word_count;
        for(int j=0; j<n; ++j) {
            int x; cin >> x;
            word_count.push_back(x);
        }

        vvi word_locations;
        for(int j=0; j<n; ++j) {
            vi word_loc;
            for(int k=0; k<word_count[j]; ++k) {
                int x; cin >> x;
                word_loc.push_back(x);
            }
            word_locations.push_back(word_loc);
        }

        mii doc; // document

        for(int j=0; j<n; ++j) {
            for(auto &l:word_locations[j]) {
                doc[l] = j;
            }
        }

        bool done = false;
        bool at_end = false;
        int snippet_length = numeric_limits<int>::max();

        mii::iterator left = doc.begin();
        mii::iterator right = doc.begin();

        while(!done) {
            if(left == right) {
                mii::iterator duplicate = right;
                ++duplicate;
                if(duplicate == doc.end())
                    break;
                else {
                    ++right;
                    continue;
                }
            }

            vi pos;
            vi pos_contents;

            mii::iterator peek = right;
            ++peek;
            for(mii::iterator it = left; it != peek; ++it) { // need to read in the last element itself
                pos.push_back(it->first);
                pos_contents.push_back(it->second);
            }

            if(has_all(pos_contents, n) && ((pos.back() - pos.front() + 1) < snippet_length)) {
                snippet_length = pos.back() - pos.front() + 1;
                ++left;
            } else if(has_all(pos_contents, n)) 
                ++left;
            else {
                if(!at_end) {
                    mii::iterator duplicate = right;
                    ++duplicate;
                    if(duplicate != doc.end())
                        ++right;
                    else {
                        at_end = true;
                        ++left;
                    }
                } else
                    ++left;
            }
        }

        cout << snippet_length << endl;
    }

    return 0;
}
