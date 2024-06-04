#include "graphbuilder.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 256

void GraphBuilder::input_number_of_vertices() {
    char buffer[MAX_LENGTH];
    long input;
    std::cin >> buffer;
    flush_cin();
    input = parse_long(buffer);
    try {
        graph.make_empty_graph(input);
    } catch (InvalidInputException& e) { invalid_input(); }
}

void GraphBuilder::input_number_of_edges() {
    const long n = graph.get_vertices_count();
    const long MAX_EDGES = (n * (n-1)) / 2;
    char buffer[MAX_LENGTH];
    long input;
    std::cin >> buffer;
    flush_cin();
    input = parse_long(buffer, true);
    if (input < 0 || input > MAX_EDGES) { invalid_input(); }
    edge_count = input;
}

void GraphBuilder::input_edges_to_graph() {
    Vertex start_vertex, end_vertex;
    char first[MAX_LENGTH], second[MAX_LENGTH];
    for (long i = 0; i < edge_count; i++) {
        std::cin >> first;
        std::cin >> second;
        flush_cin();
        start_vertex = parse_vertex(first);
        end_vertex = parse_vertex(second);
        if (start_vertex == end_vertex) { invalid_input(); }
        try {
            graph.add_edge(start_vertex, end_vertex);
        } catch (const IndexOutOfBoundsException& e) { invalid_input(); }
    }
}

void GraphBuilder::invalid_input() {
    std::cout << "invalid input";
    exit(-1);
}

void GraphBuilder::flush_cin() {
    std::cin.ignore(MAX_LENGTH, '\n');
}

long GraphBuilder::parse_long(const char *buffer, const bool include_zero) {
    constexpr long ATOL_INVALID = 0;
    long parsed_input;
    if (strcmp(buffer, "0") == 0) {
        if (include_zero) { return 0; }
        else { invalid_input(); }
    }
    parsed_input = atol(buffer);
    if (parsed_input == ATOL_INVALID) { invalid_input(); }
    return parsed_input;
}

Vertex GraphBuilder::parse_vertex(const char *buffer) {
    Vertex input = parse_long(buffer, true);
    if (input < 0 || input > graph.get_vertices_count()) {
        invalid_input();
    }
    return input;
}
