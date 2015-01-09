#include <iostream>
#include <vector>
#include <queue>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>

using namespace std;

struct vertex_info {
    int color;
    bool visited;
};

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef CGAL::Triangulation_vertex_base_with_info_2<vertex_info, K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> T;

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t;

    for(int i=0; i<t; ++i) {
        int n, m, r; cin >> n >> m >> r;

        vector<P> stations;
        for(int j=0; j<n; ++j) {
            double x, y; cin >> x >> y;
            stations.push_back(P (x, y));
        }

        vector<pair<P, P> > clues;
        for(int j=0; j<m; ++j) {
            double x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
            clues.push_back(make_pair(P (x1, y1), P(x2, y2)));
        }

        T t;
        t.insert(stations.begin(), stations.end());

        // check for interference
        for(T::Finite_vertices_iterator vit = t.finite_vertices_begin(); vit != t.finite_vertices_end(); ++vit)
            vit->info().color = -1;

        queue<T::Vertex_handle> bfs_queue;
        T::Vertex_handle first = t.finite_vertex();
        bfs_queue.push(first);
        first->info().color = 1;

        bool is_interference_free = true;
        while(!bfs_queue.empty()) {
            T::Vertex_handle current = bfs_queue.front();
            bfs_queue.pop();
            int next_color = current->info().color == 1 ? 2 : 1;

            T::Edge_circulator ec = t.incident_edges(current);
            do {
                if(!t.is_infinite(ec)) {
                    if(t.segment(ec).squared_length() <= r * r) {
                        T::Vertex_handle u = ec->first->vertex((ec->second + 1) % 3);
                        T::Vertex_handle v = ec->first->vertex((ec->second + 2) % 3);
                        if(u == current) {
                            if(v->info().color == -1) {
                                bfs_queue.push(v);
                                v->info().color = next_color;
                            } else if(v->info().color != next_color) {
                                is_interference_free = false;
                                break;
                            }
                        } else {
                            if(u->info().color == -1) {
                                bfs_queue.push(u);
                                u->info().color = next_color;
                            } else if(u->info().color != next_color) {
                                is_interference_free = false;
                                break;
                            }
                        }
                    }
                }
            } while(++ec != t.incident_edges(current));

            if(!is_interference_free)
                break;
        }

        if(!is_interference_free) {
            if(m == 1)
                cout << "n" << endl;
            else {
                for(int j=0; j<m; ++j)
                    cout << "n";
                cout << endl;
            }
        }        
        //if(!is_interference_free)
            //cout << "n" << endl;
        //else
            //cout << "y" << endl;
        // for each clue

        for(T::Finite_vertices_iterator vit = t.finite_vertices_begin(); vit != t.finite_vertices_end(); ++vit)
            vit->info().visited = false;

        for(int j=0; j<m; ++j) {
            T::Vertex_handle h_closest = t.nearest_vertex(clues[j].first);
            T::Vertex_handle w_closest = t.nearest_vertex(clues[j].second);

            if(CGAL::squared_distance(clues[j].first, h_closest->point()) <= r * r ||
                    CGAL::squared_distance(clues[j].second, w_closest->point()) <= r * r) {
                cout << "n";
                continue;
            }

            // route clues through the network
            queue<T::Vertex_handle> bfs2_queue;
            bfs2_queue.push(h_closest);
            h_closest->info().visited = true;

            bool reached = false;
            while(!bfs2_queue.empty()) {
                T::Vertex_handle current = bfs2_queue.front();
                bfs2_queue.pop();

                T::Edge_circulator ec = t.incident_edges(current);
                do {
                    if(!t.is_infinite(ec)) {
                        if(t.segment(ec).squared_length() <= r * r) {
                            T::Vertex_handle u = ec->first->vertex((ec->second + 1) % 3);
                            T::Vertex_handle v = ec->first->vertex((ec->second + 2) % 3);
                            if(u == current) {
                                if(!v->info().visited) {
                                    if(v == w_closest) {
                                        reached = true;
                                        break;
                                    }
                                    bfs2_queue.push(v);
                                    v->info().visited = true;
                                }
                            } else {
                                if(!u->info().visited) {
                                    if(u == w_closest) {
                                        reached = true;
                                        break;
                                    }
                                    bfs2_queue.push(u);
                                    u->info().visited = true;
                                }
                            }
                        }
                    }
                } while(++ec != t.incident_edges(current));

                if(reached)
                    break;
            }
            
            if(reached)
                cout << "y";
            else
                cout << "n";
        }
        cout << endl;
    }

    return 0;
}
