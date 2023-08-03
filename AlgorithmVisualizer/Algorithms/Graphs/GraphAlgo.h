#pragma once
#include <SFML/Graphics.hpp>
#include <thread>
#include <cstdlib>
#include <vector>
#include <formatCpp/formatCpp.h>
#include "../../Tile.h"

/**
 * @brief 
 * 
 * Use this as a class that will be handling a lot of the graph theory algorithms
 * 
 */

class GraphAlgo{
public:
    // Possibly use this to visualize the graph theory algorithm.
    virtual bool solve(std::vector<std::vector<sf::RectangleShape> >& map) = 0;
private:
    std::string _status; // is the status = "BFS/DFS/Dijkstras/A*, etc"
};