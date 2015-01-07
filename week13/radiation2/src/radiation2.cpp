#include<iostream>
#include<vector>
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include<CGAL/Delaunay_triangulation_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;

    for(int i=0; i<t; ++i) {
        int m, n; // m - healthy, n - cancer
        cin >> m >> n;

        vector<P> healthy;
        for(int j=0; j<m; ++j) {
            double x, y; cin >> x >> y;
            healthy.push_back(P (x, y));
        }

        vector<P> cancer;
        for(int j=0; j<n; ++j) {
            double x, y; cin >> x >> y;
            cancer.push_back(P (x, y));
        }

        
    }

    return 0;
}
