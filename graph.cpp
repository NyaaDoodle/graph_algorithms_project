#include "graph.h"
#include "exception.h"

void Graph::make_empty_graph(const long vertex_count) {
    adjacentListVector.set_length(vertex_count);
}
LinkedList<Vertex>& Graph::get_adjacent_list(const Vertex u) {
    if (u <= 0 || u > adjacentListVector.get_length()) { throw IndexOutOfBoundsException(); }
    return adjacentListVector[u-1];
}
void Graph::add_edge(const Vertex u, const Vertex v) {
    get_adjacent_list(u).push_tail(v);
}
void Graph::remove_edge(const Vertex u, const Vertex v) {
    get_adjacent_list(u).search_and_delete(v);
}
bool Graph::is_adjacent(const Vertex u, const Vertex v) {
    return get_adjacent_list(u).search(v);
}
long Graph::get_vertices_count() const {
    return adjacentListVector.get_length();
}
Graph Graph::get_condensation_graph() {
    // TODO
    return Graph();
}
