#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;

double floor_to_double(const K::FT& x) {
    double a = std::floor(CGAL::to_double(x));
    while (a > x) a -=1;
    while (a + 1 <= x) a += 1;
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << std::setprecision(0);
    int n; cin >> n;

    while (n != 0) {
        P s, a; cin >> s >> a;
        R r(s, a);

        vector<S> obstacles;
        for(int i=0; i<n; ++i) {
            double x, y; cin >> x >> y;
            P b(x, y);
            cin >> x >> y;
            P c(x, y);
            obstacles.push_back(S(b, c));
        }

        random_shuffle(obstacles.begin(), obstacles.end());

        bool hit = false;
        P intersection;
        for(vector<S>::iterator it = obstacles.begin(); it != obstacles.end(); ++it) {
            if(!hit) {
                if(CGAL::do_intersect(r, *it)) {
                    hit = true;
                    auto o = CGAL::intersection(r, *it);
                    if(const P* op = boost::get<P>(&*o))
                        intersection = *op;
                    else if(const S* os = boost::get<S>(&*o)) {
                        if(has_smaller_distance_to_point(s, os->source(), os->target()))
                            intersection = os->source();
                        else
                            intersection = os->target();
                    } else
                        // Dammit!
                        throw std::runtime_error("strange segment intersection"); 
                }
            } else {
                if(CGAL::do_intersect(S(s, intersection), *it)) {
                    auto o = CGAL::intersection(S(s, intersection), *it);
                    if(const P* op = boost::get<P>(&*o))
                        intersection = *op;
                    else if(const S* os = boost::get<S>(&*o)) {
                        if(has_smaller_distance_to_point(s, os->source(), os->target()))
                            intersection = os->source();
                        else
                            intersection = os->target();
                    }
                }
            }
        }

        if(hit)
            cout << floor_to_double(intersection.x()) << " " 
                << floor_to_double(intersection.y()) << endl;
        else
            cout << "no" << endl;

        cin >> n;
    }
}
