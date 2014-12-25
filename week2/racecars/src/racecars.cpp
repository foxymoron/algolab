#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

using namespace std;

typedef pair<int, int> pi;
typedef pair<pi, pi> ppi;

vector<pi> all_velocities = {make_pair(-1, -1), make_pair(-1, 0), make_pair(-1, 1), 
                             make_pair(0, -1), make_pair(0, 0), make_pair(0, 1),
                             make_pair(1, -1), make_pair(1, 0), make_pair(1, 1)};

int main() {
    ios_base::sync_with_stdio(false);

    int t; cin >> t;
    
    for(int i=0; i<t; ++i) {
        int X, Y; cin >> X >> Y;

        pi s, t;
        int x, y;
        cin >> x >> y; s = make_pair(x, y); // read start point
        cin >> x >> y; t = make_pair(x, y); // read end point

        vector<ppi> obstacles;
        int P; cin >> P;
        for(int j=0; j<P; ++j) {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            pi e(a, b), f(c, d);
            obstacles.push_back(make_pair(e, f));
        }

        queue<ppi> bfs_queue;
        bfs_queue.push(make_pair(s, make_pair(0, 0)));

        bool first = true;

        while(!bfs_queue.empty()) {
            ppi current = bfs_queue.front();
            bfs_queue.pop();

            string temp;
            getline(cin, temp);

            cout << "Point: " << current.first.first << " " << current.first.second;
            cout << " Velocity: " << current.second.first << " " << current.second.second << endl;
            cout << " ----------------------- " << endl;

            for(auto &v:all_velocities) {
                if(first && v == make_pair(0, 0)) {
                    first = false;
                    break;
                }
                pi new_velocity = make_pair(current.second.first + v.first, current.second.second + v.second);
                pi new_point = make_pair(current.first.first + new_velocity.first,
                                         current.first.second + new_velocity.second);

                if(!(new_point.first < 0 || new_point.first >= X || new_point.second < 0 || new_point.second >= Y)) {
                    bool blocked = false;
                    for(auto &o:obstacles) {
                        if(new_point.first <= o.second.first && new_point.first >= o.first.first) {
                            if(new_point.second <= o.second.second && new_point.second >= o.first.second) {
                                blocked = true;
                            }
                        }
                    }
                    if(!blocked) {
                        bfs_queue.push(make_pair(new_point, new_velocity));
                        cout << "Point: " << new_point.first << " " << new_point.second;
                        cout << " Velocity: " << new_velocity.first << " " << new_velocity.second << endl;
                    }
                }
            }
        }
    }
    return 0;
}
