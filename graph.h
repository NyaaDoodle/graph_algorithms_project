#pragma once
#include "vector.h"
#include "linkedlist.h"

typedef long Vertex;
enum class Color { Black, Grey, White };

class Graph {
public:
    Graph() = default;
    Graph(const Graph& g) = default;
    Graph& operator=(const Graph& g) = default;
    ~Graph() = default;
    void make_empty_graph(const long vertex_range, const bool add_all = false);
    bool is_adjacent(const Vertex u, const Vertex v);
    LinkedList<Vertex>& get_adjacent_list(const Vertex u);
    void add_edge(const Vertex u, const Vertex v);
    void remove_edge(const Vertex u, const Vertex v);
    void add_vertex(const Vertex u);
    bool does_vertex_exist(const Vertex u);
    long get_vertices_count();
    long get_vertices_range();
    LinkedList<Vertex> dfs_to_f_list();
    Graph get_transposed_graph();
    Graph get_condensation_graph();
    void print_graph();
private:
    Vector<LinkedList<Vertex>> adjacentListVector;
    Vector<bool> is_exist;
    long vertices_count = 0;
    long edges_count = 0;
    void visit_f(const Vertex u, Color color[], LinkedList<Vertex>& f);
    void visit_t(const Vertex u, Color color[], Vertex root[], Vertex current_root, Graph& target_g);
};

