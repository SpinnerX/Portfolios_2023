#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <thread>
#include <formatCpp/ofstream.h>
#include "GraphAlgo.h"
#include <unordered_set>
#include <queue>
#include <numeric>
#include <algorithm>
#include <unistd.h>
#include <stack>
#include "../../Graphics/Colors.h"

/**
 * @brief 
 * 
 * When computing DFS grid-style neighboring tiles are as follows
 * [-1, 0]
 * [1, 0]
 * [0, -1]
 * [0, 1]
 * 
 * 
 * DFS
 * uses a stack (not a queue)
 * use set to handle visited tiles.
 * 
*/

class DepthFirstSearch : public GraphAlgo{
public:
    DepthFirstSearch(Tile& start, Tile& end) : starting(start), ending(end) {}

    bool solve(std::vector<std::vector<sf::RectangleShape> >& map) override {
        formatCpp::print("Solving DFS\n");
        pathQueue.push(starting);

        while(!pathQueue.empty()){
            Tile current = pathQueue.top();
            pathQueue.pop();

            std::vector<Tile> neighbors {
                Tile(-1, 0, -1, -1, -1), // Tile{x, y, from_x, from_y, distance}
                Tile(1, 0, -1, -1, -1),
                Tile(0, 1, -1, -1, -1),
                Tile(0, -1, -1, -1, -1)
            };
            
            if(current == ending) return true;

            if(!visited.contains(current)) visited.insert(current);

            for(Tile& neighbor : neighbors){
                Tile newTile(current.x+neighbor.x, current.y+neighbor.y, current.x, current.y, -1);
                
                // If we hit a wall then we skip over this location.
                if(map[newTile.x][newTile.y].getFillColor() == Colors::lightGrey) continue;

                if((size_t)newTile.x < 0 or (size_t)newTile.x >= map.size() or newTile.y < 0 or (size_t)newTile.y >= map[0].size()) {
                    newTile.x = newTile.from_x;
                    newTile.y = newTile.from_y;
                    continue;
               }

               if(visited.contains(newTile) or map[newTile.x][newTile.y].getFillColor() == sf::Color::Red) continue;
               else map[newTile.x][newTile.y].setFillColor(sf::Color::Red);

               if(!visited.contains(newTile)) pathQueue.push(newTile);
            }
        }
        return false;
    }

private:
    Tile starting;
    Tile ending;
    std::stack<Tile> pathQueue;
    std::unordered_set<Tile> visited; // checking if specific tile has been visited.
};