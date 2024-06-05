#include "graphbuilder.h"

int main(void) {
    Graph g;
    GraphBuilder gb(g);
    gb.input_number_of_vertices();
    gb.input_number_of_edges();
    gb.input_edges_to_graph();
    Graph cg = g.get_condensation_graph();
    cg.print_graph();
    return 0;
}
