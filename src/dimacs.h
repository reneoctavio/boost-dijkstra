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
 * dimacs.h
 * boost_dijkstra
 *
 * Created by Rene Octavio Queiroz Dias on 2015-11-28.
 * GPLv3
 *
 */

#ifndef dimacs_h
#define dimacs_h

#include <string>
#include <istream>
#include <sstream>

template <typename Graph>
bool read_dimacs_graph(std::istream &dimacs, Graph &g)
{
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

            switch (ch)
            {
            case 'c':
                break;
            case 'p':
                if (vertices || edges)
                    return false;
                if (iss >> format >> vertices >> edges)
                {
                    if ("sp" != format)
                        return false;
                }
                break;
            case 'a':
                if (edges-- && (iss >> from >> to >> weight) && (add_edge(from - 1, to - 1, weight, g).second))
                    break;
            default:
                return false;
            }
        }
    }

    return !(edges || !dimacs.eof());
}

#endif /* dimacs_h */
