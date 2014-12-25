#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/MP_Float.h>

using namespace std;

typedef CGAL::MP_Float ET;
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int main() {
    ios_base::sync_with_stdio(false);

    int n, m; cin >> n >> m;

    while(n != 0 && m != 0) {
        vector<int> costs, returns;
        for(int i=0; i<n; ++i) {
            int c, r; cin >> c >> r;
            costs.push_back(c);
            returns.push_back(r);
        }

        vector<vector<int> > covariances;
        for(int i=0; i<n; ++i) {
            vector<int> cv;
            for(int j=0; j<n; ++j) {
                int v; cin >> v;
                cv.push_back(v);
            }
            covariances.push_back(cv);
        }

        for(int i=0; i<m; ++i) {
            int C, R, V; cin >> C >> R >> V;

            Program qp(CGAL::LARGER, true, 0, false, 0);
            
            // Constraint on expected return
            for(int j=0; j<n; ++j) {
                qp.set_a(j, 0, returns[j]);
            }
            qp.set_b(0, R);

            // Constraint on cost
            for(int j=0; j<n; ++j) {
                qp.set_a(j, 1, costs[j]);
            }
            qp.set_r(1, CGAL::SMALLER);
            qp.set_b(1, C);

            for(int j=0; j<n; ++j) {
                for(int k=0; k<n; ++k) {
                    if(k <= j)
                        qp.set_d(j, k, 2 * covariances[j][k]);
                }
            }

            Solution s = CGAL::solve_nonnegative_quadratic_program(qp, ET());
            assert(s.solves_quadratic_program(qp));

            if(s.is_infeasible() || s.is_unbounded() || CGAL::to_double(s.objective_value()) > V)
                cout << "No." << endl;
            else
                cout << "Yes." << endl;
        }

        cin >> n >> m;
    }

    return 0;
}
