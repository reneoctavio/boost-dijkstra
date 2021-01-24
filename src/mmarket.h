/* 
 * This file is part of the Boost Dijkstra Example Project.
 * Copyright (c) 2015 René Octavio Queiroz Dias.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * 
 * 
 * https://github.com/reneoctavio/boost-dijkstra
 *
 * mmarket.h
 * boost_dijkstra
 *
 * Created by Rene Octavio Queiroz Dias on 2015-12-04.
 * GPLv3
 *
 */

#ifndef mmarket_h
#define mmarket_h

#include <string>
#include <istream>
#include <sstream>
#include "mmio.h"
#include <boost/type_traits.hpp>

template <typename Graph>
bool read_mmatrix_unweighted_graph(std::istream &mmarket, Graph &g)
{
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

            switch (ch)
            {
            case '%':
                break;
            default:
                std::istringstream r_iss(line);
                if (comments_read)
                {
                    comments_read = false;
                    if (r_iss >> row >> col >> edges)
                        break;
                }
                else
                {
                    if (edges-- && (r_iss >> from >> to) && (add_edge(from - 1, to - 1, 1, g).second) && (add_edge(to - 1, from - 1, 1, g).second))
                        break;
                }
            }
        }
    }
    return !(edges || !mmarket.eof());
}

template <typename type>
void write_mmatrix_vector(std::ostream &mmarket, std::vector<type> &vec)
{
    // Write banner
    if (boost::is_same<type, int>())
        mmarket << "%%MatrixMarket matrix array integer general" << std::endl;
    if (boost::is_same<type, double>())
        mmarket << "%%MatrixMarket matrix array real general" << std::endl;

    // Write array size
    mmarket << vec.size() << "\t1" << std::endl;

    for (int i = 0; i < vec.size(); i++)
    {
        mmarket << vec[i] << std::endl;
    }
}

#endif /* mmarket_h */