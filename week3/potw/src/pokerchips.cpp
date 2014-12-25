#include <iostream>
#include <vector>
#include <deque>

using namespace std;

typedef vector<int> vi;
typedef deque<int> di;
typedef vector< deque<int> > vdi;

int main(){
    int t; cin >> t;
    
    for(int i=0; i<t; ++i) {
        int n; cin >> n;

        vi m;
        for(int j=0; j<n; ++j) {
            int a; cin >> a;
            m.push_back(a);
        }

        vdi c;
        for(auto &num:m) {
            di temp;
            for(int j=0; j<num; ++j) {
                int a; cin >> a;
                temp.push_back(a);
            }
            c.push_back(temp);
        }

        bool done = false;
        int score = 0;

        while(!done) {
            if(!c[0].empty() && !c[1].empty()) {
                di::reverse_iterator tos1 = c[0].rbegin();
                di::reverse_iterator tos2 = c[1].rbegin();

                if(*tos1 == *tos2) {
                    score++;
                    c[0].pop_back();
                    c[1].pop_back();
                } else if(*(tos1 + 1) == *tos2){
                    c[0].pop_back();
                } else if(*tos1 == *(tos2 + 1)) {
                    c[1].pop_back();
                } else {
                    c[0].pop_back();
                }
            } else if(!c[0].empty() && c[1].empty()) {
                c[0].pop_back();
            } else if(c[0].empty() && !c[1].empty()) {
                c[1].pop_back();
            } else if(c[0].empty() && c[1].empty()) {
                done = true;
            }
        }

        cout << score << endl;

    }
    return 0;
}
