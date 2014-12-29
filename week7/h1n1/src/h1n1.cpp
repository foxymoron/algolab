#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <utility>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<bool, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef K::Point_2 P;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;

    while(n != 0) {
        vector<P> infected;
        for(int i=0; i<n; ++i) {
            double x, y; cin >> x >> y;
            P p(x, y);
            infected.push_back(p);
        }

        Triangulation t;
        t.insert(infected.begin(), infected.end());

        int m; cin >> m;
        for(int i=0; i<m; ++i) {
            double x, y, d; cin >> x >> y >> d;
            P p(x, y);

            // check if the squared distance of a healthy
            // person is less than d to the nearest infected
            Triangulation::Vertex_handle v_closest = t.nearest_vertex(p);
            if(CGAL::squared_distance(v_closest->point(), p) < d) {
                cout << "n";
                continue;
            }

            // check if the point is already in an infinite 
            // face i.e. it's safe
            Triangulation::Face_handle f = t.locate(p);
            if(t.is_infinite(f)) {
                cout << "y";
                continue;
            }

            // if it's inside run a dfs until it goes outside
            // or the stack empties
            
            // first mark all faces as unvisited
            bool safe = false;
            for(Triangulation::Finite_faces_iterator fit = t.finite_faces_begin(); fit != t.finite_faces_end(); ++fit) {
                fit->info() = false;
            }

            stack<Triangulation::Face_handle> dfs_stack;

            dfs_stack.push(f); // the initial face

            while(!dfs_stack.empty()) {
                Triangulation::Face_handle current = dfs_stack.top();
                dfs_stack.pop();
                current->info() = true;

                for(int i=0; i<3; ++i) {
                    // check all adjacent edges
                    if(t.segment(current, i).squared_length() >= 4 * d) {
                        if(t.is_infinite(current->neighbor(i))) {
                            safe = true;
                            break;
                        } else {
                            if(!current->neighbor(i)->info())
                                dfs_stack.push(current->neighbor(i));
                        }
                    }
                }
            }

            if(safe)
                cout << "y";
            else
                cout << "n";

        }
        cout << endl;
        cin >> n;
    }

    return 0;
}
