//
//  mmarket.h
//  boost_dijkstra
//
//  Created by Rene Octavio Queiroz Dias on 12/4/15.
//  GPLv3
//

#ifndef mmarket_h
#define mmarket_h

#include <string>
#include <istream>
#include <sstream>
#include "mmio.h"
#include <boost/type_traits.hpp>

template <typename Graph>
bool read_mmatrix_unweighted_graph(std::istream& mmarket, Graph& g) {
    size_t row = 0, col = 0, edges = 0;
    bool comments_read = false;
    
    std::string line;
    while (getline(mmarket, line))
    {
        std::istringstream iss(line);
        char ch;
        if (iss >> ch)
        {
            size_t from, to;
            std::string format;
            
            switch(ch) {
                case '%' :
                    break;
                default:
                    std::istringstream r_iss(line);
                    if (comments_read) {
                        comments_read = false;
                        if (r_iss >> row >> col >> edges) break;
                    } else {
                        if (edges-- && (r_iss >> from >> to)
                            && (add_edge(from-1, to-1, 1, g).second)
                            && (add_edge(to-1, from-1, 1, g).second)) break;
                    }
            }
        }
    }
    return !(edges || !mmarket.eof());
}

template <typename type>
void write_mmatrix_vector(std::ostream& mmarket, std::vector<type>& vec) {
    // Write banner
    if (boost::is_same<type, int>()) mmarket << "%%MatrixMarket matrix array integer general" << std::endl;
    if (boost::is_same<type, double>()) mmarket << "%%MatrixMarket matrix array real general" << std::endl;

    // Write array size
    mmarket << vec.size() << "\t1" << std::endl;
    
    for (int i = 0; i < vec.size(); i++) {
        mmarket << vec[i] << std::endl;
    }
}


#endif /* mmarket_h */
