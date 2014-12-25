#include <iostream>
#include <vector>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef K::Point_2 P;
typedef CGAL::Min_circle_2_traits_2<K> Traits;
typedef CGAL::Min_circle_2<Traits> Min_circle;

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


        cout << std::setiosflags(std::ios::fixed) << 
            std::setprecision(0) <<
            ceil_to_double(sqrt(c.squared_radius())) << endl;

        cin >> n;
    }
    return 0;
}
