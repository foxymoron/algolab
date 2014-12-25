#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>

#ifdef CGAL_USE_GMP
#include <CGAL/Gmpz.h>
typedef CGAL::Gmpz ET;
#else
typedef <CGAL/MP_Float.h>
typedef CGAL::MP_Float ET;
#endif

typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int main() {
    Program lp(CGAL::SMALLER, true, 0, false, 0);

    const int X = 0;
    const int Y = 1;
    lp.set_a(X, 0, 1); lp.set_a(Y, 0, 1); lp.set_b(0, 7); // x + y <= 7
    lp.set_a(X, 1, -1); lp.set_a(Y, 1, 2); lp.set_b(1, 4); // -x + 2y <= 4
    lp.set_u(Y, true, 4); // y <= 4
    lp.set_c(Y, -32);
    lp.set_c0(64);

    Solution s = CGAL::solve_linear_program(lp, ET());
    assert (s.solves_linear_program(lp));

    std::cout << s;
    return 0;
}
