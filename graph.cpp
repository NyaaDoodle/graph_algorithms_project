#include "graph.h"
#include "exception.h"
#include <iostream>

void Graph::make_empty_graph(const long vertex_range, const bool add_all) {
    adjacentListVector.set_length(vertex_range);
    is_exist.set_length(vertex_range);
    for (long u = 1; u <= vertex_range; u++) {
        if (add_all) { add_vertex(u); }
        else { is_exist[u-1] = false; }
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
    edges_count++;
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
Graph Graph::get_transposed_graph() {
    Graph transpose_g;
    transpose_g.make_empty_graph(vertices_count, true);
    for (long u = 1; u <= vertices_count; u++) {
        for (Vertex v : get_adjacent_list(u)) {
            transpose_g.add_edge(v, u);
        }
    }
    return transpose_g;
}

Graph Graph::get_condensation_graph() {
    Graph conden_g;
    conden_g.make_empty_graph(vertices_count);
    LinkedList<Vertex> rev_f = dfs_to_f_list().get_reversed_list();
    Graph gt = get_transposed_graph();
    Color color[vertices_count];
    for (long u = 1; u <= get_vertices_count(); u++) { color[u-1] = Color::White; }
    Vertex root[vertices_count];
    Vertex current_root;
    for (Vertex u : rev_f) {
        if (color[u-1] == Color::White) {
            conden_g.add_vertex(u);
            current_root = u;
            gt.visit_t(u, color, root, current_root, conden_g);
        }
    }
    return conden_g;
}
void Graph::visit_t(const Vertex u, Color color[], Vertex root[], Vertex current_root, Graph& target_g) {
    root[u-1] = current_root;
    color[u-1] = Color::Grey;
    for (Vertex v : get_adjacent_list(u)) {
        if (color[v-1] == Color::White) {
            visit_t(v, color, root, current_root, target_g);
        }
        else if (color[v-1] == Color::Black) {
            if (root[v-1] != root[u-1]) {
                LinkedList<Vertex>& adj_list = target_g.get_adjacent_list(root[v-1]);
                if (adj_list.is_empty() || adj_list.peek_tail() != root[u-1]) {
                    target_g.add_edge(root[v-1], root[u-1]);
                }
            }
        }
    }
    color[u-1] = Color::Black;
}
void Graph::print_graph() {
    std::cout << vertices_count << ' ' << edges_count;
}
