#include <iostream>
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
    int p; std::cin >> p;

    while(p != 0) {
        if(p == 1) {
            Program qp(CGAL::SMALLER, true, 0, false, 0);
            int a, b; std::cin >> a >> b;

            const int X = 0;
            const int Y = 1;
            qp.set_a(X, 0, 1); qp.set_a(Y, 0, 1); qp.set_b(0, 4); // x + y <= 4
            qp.set_a(X, 1, 4); qp.set_a(Y, 1, 2); qp.set_b(1, a * b); // 4x + 2y <= ab
            qp.set_a(X, 2, -1); qp.set_a(Y, 2, 1); qp.set_b(2, 1); // -x + y <= 1

            qp.set_c(Y, -b);
            qp.set_d(X, X, 2 * a);

            Solution s = CGAL::solve_quadratic_program(qp, ET());
            assert(s.solves_quadratic_program(qp));

            if(s.is_infeasible())
                std::cout << "no" << std::endl;
            else if(s.is_unbounded())
                std::cout << "unbounded" << std::endl;
            else {
                std::cout << std::floor(-CGAL::to_double(s.objective_value())) << std::endl;
            }
        } else {
            Program qp(CGAL::LARGER, false, 0, false, 0);
            int a, b; std::cin >> a >> b;

            const int X = 0;
            const int Y = 1;
            const int Z = 2; // here Z is represents Z^2 in the original problem
            qp.set_a(X, 0, 1); qp.set_a(Y, 0, 1); qp.set_b(0, -4); // x + y >= -4
            qp.set_a(X, 1, 4); qp.set_a(Y, 1, 2); qp.set_a(Z, 1, 1); qp.set_b(1, -a * b); // 4x + 2y + z >= -ab
            qp.set_a(X, 2, -1); qp.set_a(Y, 2, 1); qp.set_b(2, -1); // -x + y >= -1

            qp.set_c(Y, b);
            qp.set_d(X, X, 2 * a);
            qp.set_d(Z, Z, 2);

            qp.set_u(X, true, 0);
            qp.set_u(Y, true, 0);
            qp.set_l(Z, true, 0);
            
            Solution s = CGAL::solve_quadratic_program(qp, ET());
            assert(s.solves_quadratic_program(qp));

            if(s.is_infeasible())
                std::cout << "no" << std::endl;
            else if(s.is_unbounded())
                std::cout << "unbounded" << std::endl;
            else {
                std::cout << std::ceil(CGAL::to_double(s.objective_value())) << std::endl;
                //std::cout << s.objective_value() << std::endl;
            }
        }
        cin >> p;
    }
    return 0;
}
