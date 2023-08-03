#pragma once
#include <SFML/Graphics.hpp>
#include <thread>
#include <cstdlib>
#include <vector>
#include "BFS.h"
#include "DFS.h"
#include "Dijkstras.h"

class PathfinderFactory{
public:
    // This lets us know 
    static GraphAlgo* graphStatus(Tile& starting, Tile& ending, std::string stats){
        if(stats == "BFS") return new BFS(starting, ending);
        else if(stats == "DFS") return new DepthFirstSearch(starting, ending);
        else if(stats == "Dijkstras") return new Dijkstras(starting, ending);
        return nullptr;
    }

};