#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/ch_graham_andrew.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;

bool lex_compare(const P &a, const P &b) {
    return CGAL::compare_xy(a, b) == 1 ? true : false;
}

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
        
        vector<vector<P> > map_parts;
        map_parts.reserve(n);
        for(int j=0; j<n; ++j) {
            vector<P> pts;
            pts.reserve(6);
            for(int k=0; k<6; ++k) {
                double x, y; cin >> x >> y;
                pts.push_back(P (x, y));
            }

            //for(int k=0; k<6; ++k)
                //cout << pts[k] << " ";
            //cout << endl;

            vector<P> fin;
            for(int k=0; k<6; k+=2) {
                if(CGAL::orientation(pts[k % 6], pts[(k+1) % 6], pts[(k+2) % 6]) == CGAL::LEFT_TURN) {
                    fin.push_back(pts[k]);
                    fin.push_back(pts[k+1]);
                } else {
                    fin.push_back(pts[k+1]);
                    fin.push_back(pts[k]);
                }
            }

            //for(int k=0; k<6; ++k)
                //cout << fin[k] << " ";
            //cout << endl;

            map_parts.push_back(fin);
        }

        // sort lines
        vector<vector<int> > parts_leg; // will be of size m - 1 

        for(int j=0; j<m-1; ++j) {
            vector<int> parts;
            for(int k=0; k<n; ++k) {
                bool is_blocked = false;
                for(int l=0; l<6; l+=2) {
                    if(CGAL::orientation(map_parts[k][l], map_parts[k][l+1], leg_pts[j]) == CGAL::RIGHT_TURN ||
                       CGAL::orientation(map_parts[k][l], map_parts[k][l+1], leg_pts[j+1]) == CGAL::RIGHT_TURN) {
                        is_blocked = true;
                        break;
                    }
                }
                if(!is_blocked)
                    parts.push_back(k);
            }
            //for(int k=0; k<parts.size(); ++k)
                //cout << parts[k] << " ";
            //cout << endl;
            parts_leg.push_back(parts);
        }

        vector<int> final_parts;
        for(int j=0; j<m-1; ++j) {
            if(j==0)
                final_parts.insert(final_parts.end(), parts_leg[j].begin(), parts_leg[j].end());
            else {
                vector<int> intersection;
                set_intersection(final_parts.begin(), final_parts.end(),
                                 parts_leg[j].begin(), parts_leg[j].end(),
                                 back_inserter(intersection));
                if(intersection.empty())
                    final_parts.insert(final_parts.end(), parts_leg[j].begin(), parts_leg[j].end());
                else {
                    vector<int> difference;
                    set_difference(final_parts.begin(), final_parts.end(),
                                   parts_leg[j].begin(), parts_leg[j].end(),
                                   inserter(difference, difference.begin()));
                    final_parts.clear();
                    set_union(difference.begin(), difference.end(),
                              intersection.begin(), intersection.end(),
                              back_inserter(final_parts));
                }
            }
        }

        if(final_parts.size() == 1)
            cout << final_parts.front() << endl;
        else
            cout << final_parts.back() - final_parts.front() << endl;
    }
    return 0;
}
