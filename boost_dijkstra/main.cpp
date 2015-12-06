//
//  main.cpp
//  boost_dijkstra
//
//  Created by Rene Octavio Queiroz Dias on 12/5/15.
//  GPLv3
//

#ifndef STATS
#define STATS 0
#endif

#include <iostream>
#include <fstream>
#include <string>

#include <sys/time.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/dimacs.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graphviz.hpp>

#include <boost/property_map/property_map.hpp>

#include "dimacs.h"
#include "mmarket.h"

typedef boost::adjacency_list <
boost::listS, boost::vecS,
boost::directedS,
boost::no_property,
boost::property < boost::edge_weight_t, int >
> Graph;

typedef boost::graph_traits < Graph >::vertex_descriptor vertex_descriptor;
typedef boost::graph_traits < Graph >::edge_descriptor edge_descriptor;

int main(int argc, const char * argv[]) {
    
    // Read file
    std::ifstream inGraphFile;
    inGraphFile.open(argv[2]);
    
    // Create graph
    Graph graph;
    if (std::strcmp(argv[1], "d") == 0) {
        read_dimacs_graph(inGraphFile, graph);
    } else {
        read_mmatrix_unweighted_graph(inGraphFile, graph);
    }
    
    
    // Array of distance and predecessor
    std::vector<vertex_descriptor> p(num_vertices(graph));
    std::vector<int> d(num_vertices(graph));
    
    // Initial vertex
    vertex_descriptor s = vertex(0, graph);
    
#if STATS
    int sample_size = 10;
    std::vector<double> samples(sample_size);
    
    for (int i = 0; i < sample_size; i++) {
#endif
        // Calculate elapsed time
        struct timeval tim;
        gettimeofday(&tim, NULL);
        double t1 = tim.tv_sec + (tim.tv_usec / 1000000.0);
        
        // Run dijkstra
        dijkstra_shortest_paths
        (graph, s,
         predecessor_map(
                         make_iterator_property_map(p.begin(), get(boost::vertex_index, graph))).
         distance_map(
                      make_iterator_property_map(d.begin(), get(boost::vertex_index, graph)))
         );
        
        // Calculate elapsed time
        gettimeofday(&tim, NULL);
        double t2 = tim.tv_sec + (tim.tv_usec / 1000000.0);
#if STATS
        samples[i] = t2 - t1;
        printf("Sample #: %d, Time elapsed: %.6lf seconds\n", i, t2 - t1);
    }
#else
    printf("Time elapsed: %.6lf seconds\n", t2 - t1);
#endif
    
    
#if STATS
    // Write samples to file
    std::ofstream sample_file("samples.mtx");
    write_mmatrix_vector(sample_file, samples);
    sample_file.close();
#endif
    
    // Write distances to file
    std::ofstream distance("distance.mtx");
    write_mmatrix_vector(distance, d);
    distance.close();
    
    inGraphFile.close();
    
    return 0;
}

