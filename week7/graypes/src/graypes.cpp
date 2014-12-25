#include <iostream>
#include <limits>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Edge_iterator Edge_iterator;

using namespace std;

double ceil_to_double(const K::FT& x) {
    double a = ceil(CGAL::to_double(x));
    while (a < x) a += 1;
    while (a - 1 >= x) a -= 1;
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
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

        double min_dist = numeric_limits<double>::max();
        for(Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
            double dist = ceil_to_double((sqrt(t.segment(e).squared_length()) / 2) * 100);
            if(dist < min_dist)
                min_dist = dist;
        }

        cout << setiosflags(ios::fixed) <<
            setprecision(0) <<
            min_dist << endl;

        cin >> n;
    }
    return 0;
}
