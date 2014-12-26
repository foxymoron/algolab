#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <map>

using namespace std;

typedef pair<int, int> pii;
typedef pair<pii, pii> ppi;
typedef vector<pii> vpi;
typedef map<ppi, bool> mpbi;

vpi velocities = {make_pair(-1, -1), make_pair(0, -1), make_pair(1, -1), 
                          make_pair(-1, 0),  make_pair(0, 0),  make_pair(1, 0), 
                          make_pair(-1, 1),  make_pair(0, 1),  make_pair(1, 1)};
int main() {
    int t; cin >> t;

    for(int i=0; i<t; ++i) {
        int X, Y; cin >> X >> Y;

        int s1, s2, f1, f2;
        cin >> s1 >> s2 >> f1 >> f2;

        pii s(s1, s2), f(f1, f2);

        int P; cin >> P;
        vector<ppi> obstacles;

        for(int j=0; j<P; ++j) {
            int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
            obstacles.push_back(make_pair(make_pair(x1, y1), make_pair(x2, y2)));
        }
        
        if(s == f) {
            cout << "Optimal solution takes 0 hops." << endl;
            continue;
        }
        
        queue<pair<ppi, int> > bfs_queue;
        mpbi visited;
        bfs_queue.push(make_pair(make_pair(s, make_pair(0, 0)), 0));

        visited[make_pair(s, make_pair(0, 0))] = true;

        int hops;
        bool done = false, finish_blocked = false;
        while(!bfs_queue.empty() && !done) {
            if(finish_blocked)
                break;

            pair<ppi, int> vertex = bfs_queue.front();
            bfs_queue.pop();

            for(auto &vel:velocities) {
                int n_vel_x = vertex.first.second.first + vel.first;
                int n_vel_y = vertex.first.second.second + vel.second;

                if(n_vel_x == 0 && n_vel_y == 0)
                    continue;

                if(n_vel_x <= -4 || n_vel_x >= 4 || n_vel_y <= -4 || n_vel_y >= 4)
                    continue;

                int n_x = vertex.first.first.first + n_vel_x;
                int n_y = vertex.first.first.second + n_vel_y;

                bool blocked = false;
                if(n_x < 0 || n_x > (X - 1) || n_y < 0 || n_y > (Y - 1))
                    blocked = true;
                else {
                    for(auto &o:obstacles) {
                        if(f.first >= o.first.first && f.first <= o.second.first && f.second >= o.first.second && f.second <= o.second.second) {
                            finish_blocked = true;
                            break;
                        }
                        if(n_x >= o.first.first && n_x <= o.second.first && n_y >= o.first.second && n_y <= o.second.second) {
                            blocked = true;
                            break;
                        }
                    }
                }

                if(blocked)
                    continue; // WARNING!! Maybe shitty code. If it doesn't work correct with else

                if(finish_blocked)
                    break;

                if(n_x == f.first && n_y == f.second) {
                    done = true;
                    hops = vertex.second + 1;
                    break;
                } else if(!visited[make_pair(make_pair(n_x, n_y), make_pair(n_vel_x, n_vel_y))]) {
                    bfs_queue.push(make_pair(make_pair(make_pair(n_x, n_y), make_pair(n_vel_x, n_vel_y)), vertex.second + 1));
                    visited[make_pair(make_pair(n_x, n_y), make_pair(n_vel_x, n_vel_y))] = true;
                }
            }
        }

        if(!done)
            cout << "No solution." << endl;
        else
            cout << "Optimal solution takes " << hops << " hops." << endl;
    }
    return 0;
}
