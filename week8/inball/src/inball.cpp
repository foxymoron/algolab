#include <iostream>
#include <vector>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpzf.h>

using namespace std;

typedef CGAL::Gmpzf ET;
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

typedef vector<vector<int> > vvi;

int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;

    while(n != 0) {
        int d; cin >> d;

        vvi equations(n, vector<int> ());

        for(int i=0; i<n; ++i) {
            for(int j=0; j<d; ++j) { // read all coefficients
                int a; cin >> a;
                equations[i].push_back(a);
            }
            int b; cin >> b; // read constant
            equations[i].push_back(b);
        }

        Program qp(CGAL::EQUAL, true, 0, false, 0); // equal, finite lower bound and no upper bound

        // objective function
        for(int i=0; i<d; ++i) {
            qp.set_d(i, i, -1); // minimize the negative 2-norm
        }

        // constraits
        for(int i=0; i<n; ++i) {
            // the boundaries are tangential to the the circle
            // hence the dot product between the radius vector and boundary
            // should be zero
            for(int j=0; j<d; ++j) {
                qp.set_a(j, i, equations[i][j]);
            }
            qp.set_b(i, 0); // a dot r = 0
        }

        for(int i=0; i<n; ++i) {
            // the radius should be constrained by the walls
            for(int j=0; j<d; ++j) {
                qp.set_a(j, i+n, equations[i][j]);
            }
            qp.set_b(i+n, equations[i][d]); // the radius should satisfy the inequality equation
        }

        Solution s = CGAL::solve_quadratic_program(qp, ET());
        assert(s.solves_quadratic_program(qp));

        if(s.is_infeasible())
            cout << "none" << endl;
        else if(s.is_unbounded())
            cout << "inf" << endl;
        else
            cout << floor(-CGAL::to_double(s.objective_value())) << std::endl;

        cin >> n;
    }
    
    return 0;
}
