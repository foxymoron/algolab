#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;

int main() {
    ios_base::sync_with_stdio(false);
    int c; cin >> c;

    for(int i=0; i<c; ++i) {
        int m, n; cin >> m >> n;
        // m - 1: no. of legs
        // n: no. of map parts

        vector<P> leg_pts;
        leg_pts.reserve(m);
        for(int j=0; j<m; ++j) {
            double x, y; cin >> x >> y;
            P p(x, y);
            leg_pts.push_back(p);
        }
        
        vector<vector<P> > map_parts;
        map_parts.reserve(n);
        for(int j=0; j<n; ++j) {
            vector<P> pts;
            pts.reserve(6);
            for(int k=0; k<6; ++k) {
                double x, y; cin >> x >> y;
                pts.push_back(P (x, y));
            }
            map_parts.push_back(pts);
        }

        vector<vector<int> > needed_parts; // will be of size m - 1 

    }
    return 0;
}
