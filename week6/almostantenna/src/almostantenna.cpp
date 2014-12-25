#include <iostream>
#include <algorithm>
#include <vector>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef K::Point_2 P;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;
typedef CGAL::Min_circle_2<Traits>::Support_point_iterator spi;

double ceil_to_double(const K::FT& x) {
    double a = ceil(CGAL::to_double(x));
    while (a < x) a += 1;
    while (a - 1 >= x) a -= 1;
    return a;
}

int main() {
    int n; cin >> n;

    while(n != 0) {
        vector<P> points;
        for(int i=0; i<n; ++i) {
            double x, y; cin >> x >> y; // have to
            P p(x, y);
            points.push_back(p);
        }

        random_shuffle(points.begin(), points.end());

        Min_circle mc(points.begin(), points.end(), true);
        Traits::Circle c = mc.circle();

        double min_radius = ceil_to_double(sqrt(c.squared_radius()));
        for(spi it = mc.support_points_begin(); it != mc.support_points_end(); ++it) {
            vector<P> points_copy = points;
            points_copy.erase(remove(points_copy.begin(), points_copy.end(), *it), points_copy.end());

            random_shuffle(points_copy.begin(), points_copy.end());
            Min_circle mc2(points_copy.begin(), points_copy.end(), true);
            Traits::Circle c2 = mc2.circle();

            double radius = ceil_to_double(sqrt(c2.squared_radius()));
            if(radius < min_radius)
                min_radius = radius;
        }


        cout << std::setiosflags(std::ios::fixed) << 
            std::setprecision(0) <<
            min_radius << endl;

        cin >> n;
    }
    return 0;
}
