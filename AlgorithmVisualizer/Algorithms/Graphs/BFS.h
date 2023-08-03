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
#include "../../Graphics/Colors.h"

/**
 * @brief 
 * 
 * BFS
 * uses a Queue
 * calculating neighbors we use a set to handles tiles we've visited
 * 
 * When computing BFS grid-style neighboring tiles are as follows
 * [-1, 0]
 * [1, 0]
 * [0, -1]
 * [0, 1]
 * 
 */


class BFS : public GraphAlgo {
public:
    BFS(Tile& start, Tile& end) : GraphAlgo(), starting(start), ending(end) { }

   bool solve(std::vector<std::vector<sf::RectangleShape> >& map){
        formatCpp::print("Solving BFS\n");

        std::vector<Tile> neighbors {
            Tile(-1, 0, -1, -1, -1), // Tile{x, y, from_x, from_y}
            Tile(1, 0, -1, -1, -1),
            Tile(0, 1, -1, -1, -1),
            Tile(0, -1, -1, -1, -1)
        };

        pathQueue.push(starting);
        visited.reserve(map.size() * map[0].size()); // reserve(width * height);

        while(!pathQueue.empty()){
            Tile current = pathQueue.front();
            pathQueue.pop();

            if(!visited.contains(current)) visited.insert(current);
            // if(current == ending || map[current.x][current.y].getFillColor() == sf::Color(128, 0, 128)) break; // If we are at the ending point, we break.
            
            if(current == ending || map[current.x][current.y].getFillColor() == Colors::purple) {
                map[ending.x][ending.y].setFillColor(Colors::lightGreen);
                return true; // If we are at the ending point, we break.
            }
            
            // Iterating through the neighboring tiles.
            for(size_t i = 0; i < neighbors.size(); i++){
                Tile newTile(current.x+neighbors[i].x, current.y+neighbors[i].y, current.x, current.y, -1);

                if(newTile.x < 0 or (size_t)newTile.x >= map.size() or newTile.y < 0 or (size_t)newTile.y >= map[0].size()) {
                    newTile.x = newTile.from_x;
                    newTile.y = newTile.from_y;
                }

                if(visited.contains(newTile) or map[newTile.x][newTile.y].getFillColor() == sf::Color::Red) continue;
                if(map[newTile.x][newTile.y].getFillColor() == Colors::lightGrey) continue;

                if(map[newTile.x][newTile.y].getFillColor() == sf::Color(Colors::lightGrey)) continue;
               
                map[newTile.x][newTile.y].setFillColor(sf::Color::Red);

               if(!visited.contains(newTile)) pathQueue.push(newTile);
            }
        }
        return false;
    }

private:
    Tile starting;
    Tile ending;
    std::queue<Tile> pathQueue;
    std::unordered_set<Tile> visited; // using a set to check if we already visited that
};