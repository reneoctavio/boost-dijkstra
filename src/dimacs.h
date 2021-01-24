//
//  dimacs.h
//  boost_dijkstra
//
//  Created by Rene Octavio Queiroz Dias on 11/28/15.
//  GPLv3
//

#ifndef dimacs_h
#define dimacs_h

#include <string>
#include <istream>
#include <sstream>

template <typename Graph>
bool read_dimacs_graph(std::istream& dimacs, Graph& g) {
    size_t vertices = 0, edges = 0;
    
    std::string line;
    while (getline(dimacs, line))
    {
        std::istringstream iss(line);
        char ch;
        if (iss >> ch)
        {
            size_t from, to;
            int weight;
            std::string format;
            
            switch(ch) {
                case 'c': break;
                case 'p':
                    if (vertices||edges) return false;
                    if (iss >> format >> vertices >> edges) {
                        if ("sp" != format) return false;
                    }
                    break;
                case 'a':
                    if (edges-- && (iss >> from >> to >> weight) && (add_edge(from-1, to-1, weight, g).second))
                        break;
                default:
                    return false;
            }
        }
    }
    
    return !(edges || !dimacs.eof());
}

#endif /* dimacs_h */
