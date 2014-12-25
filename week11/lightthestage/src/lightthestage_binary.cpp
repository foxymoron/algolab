#include <iostream>
#include <vector>
#include <utility>
#include <limits>
#include <cmath>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_data_structure_2<Vb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> T;

int main() {
    int t; cin >> t;

    for(int i=0; i<t; ++i) {
        int m, n; // m is no. of players, n is no. of lamps
        cin >> m >> n;

        vector<pair<P, int> > players;
        players.reserve(m);

        vector<pair<P, int> > lamps;
        lamps.reserve(n);

        for(int j=0; j<m; ++j) {
            double x, y, r; cin >> x >> y >> r;
            players.push_back(make_pair(P(x, y), r));
        }

        int h; cin >> h;

        for(int j=0; j<n; ++j) {
            double x, y; cin >> x >> y;
            lamps.push_back(make_pair(P(x, y), j));
        }

        //T t(lamps.begin(), lamps.end());


        //for(int j=0; j<m; ++j) {
            //K::FT dist = numeric_limits<double>::max();
            //int klamp = -1;
            //for(int k=0; k<n; ++k) {
                //K::FT d = CGAL::squared_distance(players[j].first, lamps[k].first);
                //if(d < dist) {
                    //dist = d;
                    //klamp = k;
                //}
            //}

            //if(dist < ((h + players[j].second) * (h + players[j].second))) {
                //if(players_killed[j] == -1 || players_killed[j] > klamp)
                    //players_killed[j] = klamp;
            //}
        //}
        bool done = false;
        bool first = true;

        int high = n;

        vector<int> winners;
        int last_count = 0;
        
        int last_high;

        while(!done) {
            vector<int> winners_local;
            int count = 0;

            T t(lamps.begin(), lamps.begin() + high);

            for(int j=0; j<m; ++j) {
                T::Vertex_handle v = t.nearest_vertex(players[j].first);
                //cout << v->info() << " ";
                K::FT dist = sqrt(CGAL::squared_distance(v->point(), players[j].first));
                if(floor(dist) >= (h + players[j].second)) {
                    winners_local.push_back(j);
                    count++;
                }
            }
            //cout << endl;
            if(count != m) {
                if(first) {
                    done = true;
                    winners = winners_local;
                    last_count = count;
                } else {
                    if(count < last_count) {
                        // go up
                        winners = winners_local;
                        last_count = count;
                        high = high + ((last_high - high) / 2);
                        last_high = high;
                    } else {
                        // go down
                        winners = winners_local;
                        last_count = count;
                        high = high - ((last_high - high) / 2);
                        last_high = high;
                    }
                }
            } else {
                if(first) {
                    first = false;
                    winners = winners_local;
                    last_count = count;
                    last_high = high;
                    high = high / 2;
                } else {
                    // we're done here, need to return as the last rounds winners are already
                    // in the players_killed vector
                    if(last_high - 1 == high)
                        done = true;
                    else {
                        winners = winners_local;
                        last_count = count;
                        high = high - ((last_high - high) / 2);
                        last_high = high;
                    }
                }
            }

        }

        for(int &p:winners)
            cout << p << " ";
        cout << endl;
    }
    return 0;
}
