#include<iostream>
#include<vector>
#include<queue>
#include<set>

using namespace std;

typedef vector<int> vi;
typedef vector<vector<int> > vii;

int main() {
	std::ios_base::sync_with_stdio(false);
	int t; cin >> t;
	for (int i = 0; i < t; i++) {
		int V, E; cin >> V >> E;		
		int s, t; cin >> s >> t;
		s--; t--;
		
		vi visited(V, 0);
		vi distances(V, 0);
		vii graph; 
				 
		// Create an empty graph as a vector of vectors (inside vector holds the neighbors of a vertex)
		for (int j = 0; j < V; j++) {
			vi neighbors;
			graph.push_back(neighbors);
		}
		
		// Fill the graph by pushing the edges 
		for (int j = 0; j < E; j++ ) {
			int first, second; cin >> first >> second;
			graph[first-1].push_back(second-1);
		}
					
		queue<pair<int, int> > vertices; // Queue stores vertex and its distance from start point
		vertices.push(make_pair(s, 0));
		
		int solution = -1;
		int done = 0;
		
		visited[s] = 1;
		
		while(!vertices.empty() && done == 0) {
			pair<int, int> current = vertices.front();
			vertices.pop();
			int vertex = current.first;
			int distance = current.second;
		
			for (auto &komsija : graph[vertex]) {			
				if (visited[komsija] < 2) {
					vertices.push(make_pair(komsija, distance + 1));					
					visited[komsija]++;

					if (komsija == t && visited[komsija] == 2) {
						solution = distance + 1;
						done = 1;
						break;
					}	
				}			
			}  
		} 
		if (solution >= 0)
        		cout << solution << "\n";
        	else
        		cout << "no" << "\n";
    }
    return 0;
}
