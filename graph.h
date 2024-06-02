#pragma once
#include "vector.h"
#include "linkedlist.h"

typedef size_t Vertex;

class Graph() {
public:
    void make_empty_graph(const size_t vertex_count);
    bool is_adjacent(const Vertex u, const Vertex v) const;
    LinkedList<Vertex> get_adjacent_list(const Vertex u) const;
    void add_edge(const Vertex u, const Vertex v);
    void remove_edge(const Vertex u, const Vertex v);
    Graph get_condensation_graph();
    void print_condensation_graph(Graph con_graph);
private:
    Vector<LinkedList<Vertex>> adjacentListVector;
};

