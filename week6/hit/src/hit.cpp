#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;

int main() {
    int n; cin >> n;

    while (n != 0) {
        P s, a; cin >> s >> a;
        R r(s, a);

        vector<S> obstacles;
        for(int i=0; i<n; ++i) {
            P b, c; cin >> b >> c;
            obstacles.push_back(S(b, c));
        }

        bool hit = false;
        for(vector<S>::iterator it = obstacles.begin(); it != obstacles.end(); ++it) {
            if(CGAL::do_intersect(r, *it)) {
                hit = true;
                break;
            }
        }

        if(hit)
            cout << "yes" << endl;
        else
            cout << "no" << endl;

        cin >> n;
    }
}
