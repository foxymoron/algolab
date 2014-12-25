#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

using namespace std;

typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int main() {
    ios_base::sync_with_stdio(false);
    cout << setiosflags(ios::fixed) << setprecision(0);

    int n, m; cin >> n >> m;

    while(n != 0 && m != 0) {
        Program qp(CGAL::SMALLER, true, 0, false, 0);

        vector<int> min, max;
        min.reserve(n); max.reserve(n);

        for(int i=0; i<n; ++i) {
            int mn, mx; cin >> mn >> mx;
            min.push_back(mn); max.push_back(mx);
        }

        vector< vector<int> > nutrientspf;
        for(int i=0; i<m; ++i) {
            int cost; cin >> cost;
            // objective function
            qp.set_c(i, cost);

            vector<int> nutrients;
            for(int j=0; j<n; ++j) {
                int x; cin >> x;
                nutrients.push_back(x);
            }
            nutrientspf.push_back(nutrients);
        }

        // minimum constraints
        for(int i=0; i<n; ++i) {
            for(int j=0; j<m; ++j) {
                qp.set_a(j, i, nutrientspf[j][i]);
            }
            qp.set_r(i, CGAL::LARGER);
            qp.set_b(i, min[i]);
        }

        // maximum constraints
        for(int i=0; i<n; ++i) {
            for(int j=0; j<m; ++j) {
                qp.set_a(j, i + n, nutrientspf[j][i]);
            }
            qp.set_r(i + n, CGAL::SMALLER);
            qp.set_b(i + n, max[i]);
        }

        Solution s = CGAL::solve_quadratic_program(qp, ET());
        assert(s.solves_quadratic_program(qp));

        if(s.is_infeasible() || s.is_unbounded())
            cout << "No such diet." << endl;
        else
            cout << floor(CGAL::to_double(s.objective_value())) << endl;

        cin >> n >> m;
    }

    return 0;
}
