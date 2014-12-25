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

        T t(lamps.begin(), lamps.end());

        vector<int> winners;

        for(int j=0; j<m; ++j) {
            T::Vertex_handle v = t.nearest_vertex(players[j].first);
            //cout << v->info() << " ";
            K::FT dist = sqrt(CGAL::squared_distance(v->point(), players[j].first));
            if(floor(dist) >= (h + players[j].second))
                winners.push_back(j);
        }

        if(winners.size() != 0) {
            for(auto &w:winners)
                cout << w << " ";
            cout << endl;
        } else {
            vector<int> player_lamp(m, -1);
            for(int j=0; j<m; ++j) {
                for(int k=0; k<n; ++k) {
                    K::FT dist = sqrt(CGAL::squared_distance(players[j].first, lamps[k].first));
                    if(floor(dist) < (h + players[j].second)) {
                        player_lamp[j] = k;
                        break;
                    }
                }
            }

            int last_lamp = *max_element(player_lamp.begin(), player_lamp.end());

            for(int j=0; j<m; ++j)
                if(player_lamp[j] == last_lamp)
                    cout << j << " ";
            cout << endl;
        }
    }
    return 0;
}
