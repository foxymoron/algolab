#include <iostream>
#include <vector>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef CGAL::Triangulation_vertex_base_with_info_2<bool, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef Triangulation::Edge_iterator Edge_iterator;

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;

    for(int i=0; i<t; ++i) {
        int n, d; cin >> n >> d;
        
        vector<P> planes;
        for(int j=0; j<n; ++j) {
            int x, y; cin >> x >> y;
            P p(x, y);
            planes.push_back(p);
        }

        Triangulation t;
        t.insert(planes.begin(), planes.end());

        Triangulation::Finite_vertices_iterator vit;
        for(vit = t.finite_vertices_begin(); vit != t.finite_vertices_end(); ++vit) {
            vit->info() = false;
        }

        int count = 0;
        for(Edge_iterator e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
            //cout << CGAL::to_double(sqrt(t.segment(e).squared_length())) << endl;
            if(CGAL::to_double(sqrt(t.segment(e).squared_length())) < d) {
                Triangulation::Vertex_handle v1 = e->first->vertex((e->second + 1) % 3);
                Triangulation::Vertex_handle v2 = e->first->vertex((e->second + 2) % 3);
                //cout << v1->point() << " " << v1->info() << endl;
                //cout << v2->point() << " " << v2->info() << endl;
                if(!v1->info()) {
                    count++;
                    v1->info() = true;
                }
                if(!v2->info()) {
                    count++;
                    v2->info() = true;
                }
            }
        }

        cout << count << endl;
    }
    return 0;
}
