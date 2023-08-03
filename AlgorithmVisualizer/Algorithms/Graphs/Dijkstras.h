#pragma once
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

class Dijkstras : public GraphAlgo{
public:
    Dijkstras(Tile& start, Tile& end) : starting(start), ending(end) {}

    bool solve(std::vector<std::vector<sf::RectangleShape>>& map) override {
        formatCpp::print("Solving Dijkstras\n");

        pathQueue.push(starting);

        std::vector<Tile> neighbors {
            Tile(-1, 0, -1, -1, -1), // Tile{x, y, from_x, from_y}
            Tile(1, 0, -1, -1, -1),
            Tile(0, 1, -1, -1, -1),
            Tile(0, -1, -1, -1, -1)
        };

        while(!pathQueue.empty()){
            Tile current = pathQueue.top();
            pathQueue.pop();
            
            // Making sure once we reached the end we break and change that ending point  from
            // purple to green, indicating we found the target
            if(current == ending || map[current.x][current.y].getFillColor() == Colors::purple){
                map[ending.x][ending.y].setFillColor(Colors::lightGreen);
            }

            if(map[current.x][current.y].getFillColor() == Colors::lightGrey) continue;

            // We also want to check if the current tile has been visited,
            // if not visited we add into the set<Tile>
            if(!visited.contains(current)) visited.insert(current);
            

            // iterating through all the tile neighbors
            for(Tile neighbor : neighbors){
                Tile newTile(current.x+neighbor.x, current.y+neighbor.y, current.x, current.y, -1);

                if(map[newTile.x][newTile.y].getFillColor() == Colors::lightGrey) continue;

                // We are checking if the tile is out if bounds
                // new tile must not be greater then the width and height of the map.
                if((size_t)newTile.x < 0 or (size_t)newTile.x >= map.size() or newTile.y < 0 or (size_t)newTile.y >= map[0].size()) {
                    newTile.x = newTile.from_x;
                    newTile.y = newTile.from_y;
                    continue;
                }



                // We dont want to check tiles that have already been indicated that its been visited.
                if(visited.contains(newTile) or map[newTile.x][newTile.y].getFillColor() == sf::Color::Red) continue;
                map[newTile.x][newTile.y].setFillColor(sf::Color::Red);

                if(!visited.contains(newTile)) pathQueue.push(newTile);
            }
        }

        return false;
    }

private:
    // Backtracking Dijkstras algorithm
    bool backtracking(Tile& current){
        while(true){
            if(current.from_x == starting.x and ending.from_x == starting.from_x) break;

            Tile temp(current.from_x, current.from_y, -1, -1, -1);

            auto iter = visited.find(temp);
            current = *iter;

            sf::seconds(5);
        }

        return false;
    }


private:
    std::priority_queue<Tile, std::vector<Tile>, Tile_Comp> pathQueue;
    std::unordered_set<Tile> visited;
    Tile starting;
    Tile ending;
};