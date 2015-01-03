#include <iostream>
#include <vector>
#include <limits>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Point_2<K> P;
typedef CGAL::Segment_2<K> S;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef Triangulation::Vertex_iterator Vertex_iterator;
typedef Triangulation::Edge_iterator Edge_iterator;

double ceil_to_double(const K::FT& x) {
    double a = ceil(CGAL::to_double(x));
    while (a < x) a += 1;
    while (a - 1 >= x) a -= 1;
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    int n; cin >> n;

    while(n != 0) {
        double l, b, r, t; cin >> l >> b >> r >> t;

        vector<S> walls;
        walls.push_back(S(P(l, t), P(l, b)));
        walls.push_back(S(P(l, b), P(r, b)));
        walls.push_back(S(P(r, t), P(r, b)));
        walls.push_back(S(P(l, t), P(r, t)));
        
        vector<pair<P, int> > points;
        for(int j=0; j<n; ++j) {
            double x, y; cin >> x >> y;
            points.push_back(make_pair(P(x, y), j));
        }

        Triangulation tr;
        tr.insert(points.begin(), points.end());

        vector<double> death_times(n, numeric_limits<int>::max());

        // find the closest wall for each 
        for(Vertex_iterator v = tr.finite_vertices_begin(); v != tr.finite_vertices_end(); ++v) {
            for(int i=0; i<4; ++i) {
                K::FT d = sqrt(CGAL::squared_distance(v->point(), walls[i]));
                d = sqrt(d - 0.5);
                if(ceil_to_double(d) < death_times[v->info()])
                    death_times[v->info()] = ceil_to_double(d);
            }
        }
        
        //for(int i=0; i<n; ++i)
            //cout << death_times[i] << " ";
        //cout << endl;

        // now check the neighbors
        for(Edge_iterator e = tr.finite_edges_begin(); e != tr.finite_edges_end(); ++e) {
            K::FT d = sqrt(tr.segment(e).squared_length());
            d = d / 2;
            d = sqrt(d - 0.5);

            // Get vertices
            Triangulation::Vertex_handle v1 = e->first->vertex((e->second + 1) % 3);
            Triangulation::Vertex_handle v2 = e->first->vertex((e->second + 2) % 3);
            if(ceil_to_double(d) < death_times[v1->info()])
                death_times[v1->info()] = ceil_to_double(d);
            if(ceil_to_double(d) < death_times[v2->info()])
                death_times[v2->info()] = ceil_to_double(d);
        }

        //for(int i=0; i<n; ++i)
            //cout << death_times[i] << " ";
        //cout << endl;

        sort(death_times.begin(), death_times.end());

        if(n == 1)
            cout << death_times[0] << " " << death_times[0] << " " << death_times[0] << endl;
        else
            cout << death_times[0] << " " << death_times[n/2] << " " << death_times[n-1] << endl;

        cin >> n;
    }

    return 0;
}
