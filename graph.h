#pragma once
#include "vector.h"
#include "linkedlist.h"

typedef long Vertex;

class Graph {
public:
    Graph() = default;
    Graph(const Graph& g) = delete;
    Graph& operator=(const Graph& g) = delete;
    ~Graph() = default;
    void make_empty_graph(const long vertex_count);
    bool is_adjacent(const Vertex u, const Vertex v);
    LinkedList<Vertex>& get_adjacent_list(const Vertex u);
    void add_edge(const Vertex u, const Vertex v);
    void remove_edge(const Vertex u, const Vertex v);
    long get_vertices_count();
    Graph get_condensation_graph();
    void print_graph();
private:
    Vector<LinkedList<Vertex>> adjacentListVector;
};

