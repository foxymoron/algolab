#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;

double floor_to_double(const K::FT& x) {
    double a = std::floor(CGAL::to_double(x));
    while (a > x) a -=1;
    while (a + 1 <= x) a += 1;
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(0);
    int n; cin >> n;

    while(n != 0) {
        vector<P> pts;
        pts.reserve(n);
        for(int i=0; i<n; ++i) {
            double x, y; cin >> x >> y;
            P p(x, y);
            pts.push_back(p);
        }

        Triangulation t;
        t.insert(pts.begin(), pts.end());

        int m; cin >> m;
        for(int i=0; i<m; ++i) {
            double x, y; cin >> x >> y;
            P p(x, y);

            cout << floor_to_double(CGAL::squared_distance(
                        t.nearest_vertex(p)->point(), p)) << endl;
        }

        cin >> n;
    }
    return 0;
}
