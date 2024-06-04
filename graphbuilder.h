#pragma once
#include "graph.h"

class GraphBuilder {
public:
    GraphBuilder(Graph& graph) : graph(graph) {}
    void input_number_of_vertices();
    void input_number_of_edges();
    void input_edges_to_graph();
private:
    Graph& graph;
    long edge_count = 0;
    void invalid_input();
    void flush_cin();
    long parse_long(const char *buffer, const bool include_zero = false);
    Vertex parse_vertex(const char *buffer);
};
