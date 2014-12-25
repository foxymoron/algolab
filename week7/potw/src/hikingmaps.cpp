#include <iostream>
#include <set>
#include <algorithm>
#include <vector>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Line_2 L;
typedef K::Triangle_2 T;

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

        vector<T> map_parts;
        map_parts.reserve(n);
        for(int j=0; j<n; ++j) {
            vector<P> pts;
            pts.reserve(6);
            for(int k=0; k<6; ++k) {
                double x, y; cin >> x >> y;
                P p(x, y);
                pts.push_back(p);
            }

            L l1(pts[0], pts[1]),
              l2(pts[2], pts[3]),
              l3(pts[4], pts[5]);

            P p1, p2, p3;

            auto o1 = CGAL::intersection(l1, l2);
            if(const P* op1 = boost::get<P>(&*o1))
                p1 = *op1;
            else
                throw std::runtime_error("strange intersection, wanted a point");

            auto o2 = CGAL::intersection(l2, l3);
            if(const P* op2 = boost::get<P>(&*o2))
                p2 = *op2;
            else
                throw std::runtime_error("strange intersection, wanted a point");

            auto o3 = CGAL::intersection(l1, l3);
            if(const P* op3 = boost::get<P>(&*o3))
                p3 = *op3;
            else
                throw std::runtime_error("strange intersection, wanted a point");

            T t(p1, p2, p3);
            map_parts.push_back(t);
        }

        set<int> required_parts;
        for(int j=0; j<m-2; ++j) {
            for(int k=0; k<n; ++k) {
                if(CGAL::do_intersect(map_parts[k], S(leg_pts[j], leg_pts[j+1]))) {
                    auto o = CGAL::intersection(map_parts[k], S(leg_pts[j], leg_pts[j+1]));
                    if(const S* os = boost::get<S>(&*o)) {
                        if(*os == S(leg_pts[j], leg_pts[j+1])) {
                            cout << "Intersection" << endl;
                            required_parts.insert(k);
                        }
                    } else
                        continue;
                }
            }
        }

        for(auto &val:required_parts)
            cout << val << " " ;
        cout << endl;
    }
    return 0;
}
