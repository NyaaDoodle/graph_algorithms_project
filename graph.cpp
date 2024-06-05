#include "graph.h"
#include "exception.h"
#include <iostream>

Graph::Graph(const Graph& g) {
    
}
void Graph::make_empty_graph(const long vertex_range) {
    adjacentListVector.set_length(vertex_range);
    is_exist.set_length(vertex_range);
    for (long i = 0; i < vertex_range; i++) {
        is_exist[i] = false;
    }
}
LinkedList<Vertex>& Graph::get_adjacent_list(const Vertex u) {
    if (u <= 0 || u > get_vertices_range()) { throw IndexOutOfBoundsException(); }
    if (!does_vertex_exist(u)) { throw VertexNotAdded(); }
    return adjacentListVector[u-1];
}
void Graph::add_edge(const Vertex u, const Vertex v) {
    if (!(does_vertex_exist(u) && does_vertex_exist(v))) { throw VertexNotAdded(); }
    get_adjacent_list(u).push_tail(v);
}
void Graph::remove_edge(const Vertex u, const Vertex v) {
    if (!(does_vertex_exist(u) && does_vertex_exist(v))) { throw VertexNotAdded(); }
    get_adjacent_list(u).search_and_delete(v);
}
bool Graph::is_adjacent(const Vertex u, const Vertex v) {
    if (!(does_vertex_exist(u) && does_vertex_exist(v))) { throw VertexNotAdded(); }
    return get_adjacent_list(u).search(v);
}
void Graph::add_vertex(const Vertex u) {
    if (u <= 0 || u > get_vertices_range()) { throw IndexOutOfBoundsException(); }
    is_exist[u-1] = true;
    vertices_count++;
}
bool Graph::does_vertex_exist(const Vertex u) {
    if (u <= 0 || u > get_vertices_range()) { throw IndexOutOfBoundsException(); }
    return is_exist[u-1];
}
long Graph::get_vertices_count() {
    return vertices_count;
}
long Graph::get_vertices_range() {
    return adjacentListVector.get_length();
}
LinkedList<Vertex> Graph::dfs_to_f_list() {
    // Assuming all vertices from 1 to n have been added.
    LinkedList<Vertex> f;
    Color color[get_vertices_count()];
    for (long u = 1; u <= get_vertices_count(); u++) { color[u-1] = Color::White; }
    for (long u = 1; u <= get_vertices_count(); u++) {
        if (color[u-1] == Color::White) { visit_f(u, color, f); }
    }
    return f;
}
void Graph::visit_f(const Vertex u, Color color[], LinkedList<Vertex>& f) {
    color[u-1] = Color::Grey;
    for (Vertex v : get_adjacent_list(u)) {
        if (color[v-1] == Color::White) {
            visit_f(v, color, f);
        }
    }
    color[u-1] = Color::Black;
    f.push_tail(u);
}
//Graph Graph::get_transposed_graph() {
//    return Graph();
//}
//Graph Graph::get_condensation_graph() {
//    return Graph();
//}
void Graph::print_graph() {
    const long n = get_vertices_range();
    for (long u = 1; u <= n; u++) {
        if (does_vertex_exist(u)) {
            for (Vertex v : get_adjacent_list(u)) {
                std::cout << '(' << u << ',' << v << ')' << ' ';
            }
        }
    }
    std::cout << std::endl;
}
