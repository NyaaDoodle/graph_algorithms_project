#pragma once
#include "graph.h"

class GraphBuilder {
public:
    void input_number_of_vertices();
    void input_number_of_edges();
    void input_edges_to_graph(const size_t edge_count);
private:
    const Graph& graph;
};
