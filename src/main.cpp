#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

#include "GraphTheory.h"

void read(
    raven::graph::sGraphData &graphData,
    int &capacity,
    const std::string &fname)
{
    std::ifstream ifs(fname);
    if (!ifs.is_open())
        throw std::runtime_error(
            "Cannot open " + fname);

    graphData.g.clear();
    graphData.multiStart.clear();

    std::string stype, sn1, sn2, scost, directed, same;
    ifs >> stype;

    while (ifs.good())
    {
        switch (stype[0])
        {
        case 'g':
            if (graphData.g.vertexCount())
                throw std::runtime_error(
                    "g ( graph mode ) must be second line");
            ifs >> directed >> same;
            if (directed == "1")
                graphData.g.directed();
            break;
        case 'l':
            ifs >> sn1 >> sn2 >> scost;
            graphData.g.add(sn1, sn2);
            graphData.edgeWeight.push_back(atof(scost.c_str()));
            if ((!graphData.g.isDirected()) && same == "1")
            {
                graphData.edgeWeight.push_back(atof(scost.c_str()));
            }
            break;
        case 's':
            ifs >> graphData.startName;
            graphData.multiStart.push_back(graphData.startName);
            break;
        case 'e':
            ifs >> graphData.endName;
            break;
        case 'c':
            ifs >> capacity;
        }

        ifs >> stype;
    }
}
int countChargeStops(
    raven::graph::sGraphData &gd,
    std::vector<int> &vPath,
    int capacity)
{
    int tank = capacity;
    int stops = 0;
    for( auto it = vPath.begin(); it != vPath.end()-1; it++ )
    {
        int dist = gd.edgeWeight[gd.g.find(*it,*(it+1))];
        if( dist < tank ) {
            // next vertex reachable with charge remaining
            tank -= dist;
            continue;
        }
        // recharging stop
        tank = capacity;
        stops++;
    }
    return stops;
}

main(int argc, char *argv[])
{
    raven::graph::sGraphData gd;
    int capacity;
    
    read(gd, capacity, argv[1]);

    // find all paths between start and end
    // in increasing length order
    // uses Yen's algorithm

    auto vpath = raven::graph::allPaths(gd);

    bool feasible = false;
    for (auto &p : vpath)
    {
        // check that longest hop in path can be covered with a full charge
        if (*std::max_element(p.first.begin(), p.first.end()) > capacity)
            continue;

        // feasible path found
        feasible = true;
        for (int v : p.first)
        {
            std::cout << gd.g.userName(v) << " ";
        }
        std::cout << " with " 
            << countChargeStops(gd, p.first, capacity)
            << " stops\n";
        break;
    }

    if (!feasible)
        std::cout << "no feasible path\n";
        
    return 0;
}
