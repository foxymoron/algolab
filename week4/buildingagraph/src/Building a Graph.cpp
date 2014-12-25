#include<iostream>
#include<vector>

#include<boost/graph/adjacency_list.hpp>
#include<boost/graph/dijkstra_shortest_paths.hpp>
#include<boost/tuple/tuple.hpp>
#include<boost/graph/kruskal_min_spanning_tree.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, no_property, 
						property<edge_weight_t, int> > Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef property_map<Graph, edge_weight_t>::type WeightMap;

int main() {
	std::ios_base::sync_with_stdio(false);
	int t; cin >> t;
	
	for (int i = 0; i < t; ++i) {
		int V, E; cin >> V >> E;
		
		Graph G(V);
		WeightMap weightMap = get(edge_weight, G);
		
		for (int j = 0; j < E; ++j) {
			int u, v, w; cin >> u >> v >> w;
			Edge e;
			tie(e, tuples::ignore) = add_edge(u, v, G);
			weightMap[e] = w;
		}
		
		vector<Edge> spanning_tree;
		kruskal_minimum_spanning_tree(G, back_inserter(spanning_tree));
		
		int sum = 0;
		for (auto e : spanning_tree)
			sum += weightMap[e];
		
		vector<int> dist(V);
		dijkstra_shortest_paths(G, 0, distance_map(&dist[0]));
		
		int max_dist = 0;
		for (auto vertex : dist) {
			if (vertex > max_dist)
				max_dist = vertex;		
		}
		cout << sum << " " << max_dist << endl;
	}
	return 0;
}