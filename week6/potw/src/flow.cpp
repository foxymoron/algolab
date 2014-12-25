#include <iostream>
#include <algorithm>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>
#include <boost/tuple/tuple.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;
typedef adjacency_list<vecS, vecS, directedS, no_property,
    property<edge_capacity_t, long,
        property<edge_residual_capacity_t, long,
            property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;
typedef property_map<Graph, edge_capacity_t>::type      EdgeCapacityMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type       ReverseEdgeMap;
typedef graph_traits<Graph>::vertex_descriptor          Vertex;
typedef graph_traits<Graph>::edge_descriptor            Edge;



// Custom add_edge, also creates reverse edges with corresponding capacities.
void addEdge(int u, int v, long c, EdgeCapacityMap &capacity, ReverseEdgeMap &rev_edge, Graph &G) {
    Edge e, reverseE;
    tie(e, tuples::ignore) = add_edge(u, v, G);
    tie(reverseE, tuples::ignore) = add_edge(v, u, G);
    capacity[e] = c;
    capacity[reverseE] = 0;
    rev_edge[e] = reverseE;
    rev_edge[reverseE] = e;
}


int main() {
    // Create Graph and Maps
    Graph G(5);
    EdgeCapacityMap capacity = get(edge_capacity, G);
    ReverseEdgeMap  rev_edge = get(edge_reverse, G);
    ResidualCapacityMap res_capacity = get(edge_residual_capacity, G);

    // Add edges
    addEdge(0, 4, 1, capacity, rev_edge, G);
    addEdge(4, 0, 1, capacity, rev_edge, G);
    addEdge(0, 2, 1, capacity, rev_edge, G);
    addEdge(2, 0, 1, capacity, rev_edge, G);
    addEdge(1, 2, 1, capacity, rev_edge, G);
    addEdge(2, 1, 1, capacity, rev_edge, G);
    addEdge(1, 3, 2, capacity, rev_edge, G);
    addEdge(3, 1, 2, capacity, rev_edge, G);

    // Add source and sink
    Vertex source = add_vertex(G);
    Vertex sink = add_vertex(G);
    addEdge(source, 1, 1, capacity, rev_edge, G);
    addEdge(source, 3, 3, capacity, rev_edge, G);
    addEdge(0, sink, 3, capacity, rev_edge, G);
    addEdge(4, sink, 2, capacity, rev_edge, G);
    addEdge(2, sink, 1, capacity, rev_edge, G);

    // Calculate flow
    long flow1 = push_relabel_max_flow(G, source, sink);
    long flow2 = edmonds_karp_max_flow(G, source, sink);
    cout << flow1 << endl;

    return 0;
}

