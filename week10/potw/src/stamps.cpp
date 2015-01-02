#include <iostream>
#include <vector>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/MP_Float.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

using namespace std;

typedef CGAL::MP_Float ET;
typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Point_2<K> P;
typedef CGAL::Segment_2<K> S;

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;

    for(int i=0; i<t; ++i) {
        int l, s, w; cin >> l >> s >> w;

        vector<P> lamps;
        for(int j=0; j<l; ++j) {
            double x, y; cin >> x >> y;
            lamps.push_back(P (x, y));
        }

        vector<pair<P, double> > stamps;
        for(int j=0; j<s; ++j) {
            double x, y, M; cin >> x >> y >> M;
            stamps.push_back(make_pair(P (x, y), M));
        }

        vector<S> walls;
        for(int j=0; j<w; ++j) {
            double a, b, c, d; cin >> a >> b >> c >> d;
            walls.push_back(S(P(a, b), P(c, d)));
        }

        vector<vector<bool> > is_blocked(s, vector<bool> (l, false));
        for(int j=0; j<s; ++j) {
            for(int k=0; k<l; ++k) {
                for(int m=0; m<w; ++m) {
                    if(CGAL::do_intersect(walls[m], S(stamps[j].first, lamps[k])))
                        is_blocked[j][k] = true;
                }
            }
        }

        Program lp(CGAL::SMALLER, true, 1, true, 1<<12);

        for(int j=0; j<s; ++j) {
            for(int k=0; k<l; ++k) {
                double coeff = 0;
                if(!is_blocked[j][k])
                    coeff = 1.0/CGAL::squared_distance(stamps[j].first, lamps[k]);
                lp.set_a(k, j, coeff);
                lp.set_a(k, j + s, coeff);
            }
            lp.set_b(j, stamps[j].second);
            lp.set_r(j + s, CGAL::LARGER);
            lp.set_b(j + s, 1.0);
        }

        Solution sol = solve_linear_program(lp, ET());
        assert(sol.solves_linear_program(lp));

        if(sol.is_infeasible())
            cout << "no" << endl;
        else
            cout << "yes" << endl;
    }
    return 0;
}
