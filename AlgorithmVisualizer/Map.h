#pragma once
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <numeric>
#include <formatCpp/formatCpp.h>
#include "Algorithms/Graphs/PathfinderFactory.h"
#include <SFML/Graphics.hpp>

/**
 * @brief 
 * 
 * This allows us to create a map to do stuff like graph theory, and other algo visualization.
 * 
 */
class Map{
public:
    Map() = default;
    Map(unsigned int row, unsigned col) {
        tiles = std::vector<std::vector<sf::RectangleShape> >(row, std::vector<sf::RectangleShape>(col));
        cellSize = sf::Vector2f(25.f, 25.f);
        isSolved = false;
    }

    sf::Vector2f cell_size() { return cellSize; }

    std::size_t rows() { return tiles.size(); }
    std::size_t cols() { return tiles[0].size(); }

    // This is just to test that the map can be drawn before implementing it.
    void generate(){
        for(size_t row = 0; row < tiles.size(); row++){
            for(size_t col = 0; col < tiles[0].size(); col++){
                tiles[row][col].setSize(cellSize);
                tiles[row][col].setOutlineColor(sf::Color(211, 211, 211));
                tiles[row][col].setOutlineThickness(1.f);
                const float offset = 5.f; // Offset allows to change the position of where the map is in the window.
                tiles[row][col].setPosition(row * cellSize.x + offset, col * cellSize.y + offset);
            }
        }
    }

    // The idea is we use a dropdown menu to say which algorithm to use and then grab the starting and ending point here.
    void solve(Tile& starting, Tile& ending, std::string name){
        // This takes the starting and ending points and allowing us to use the obj bfs to handle the breadth first search algo.
        GraphAlgo* graph = PathfinderFactory::graphStatus(starting, ending, name);
        formatCpp::print("Boolean value before graph solved! {}\n", isSolved);
        if(graph != nullptr) isSolved = graph->solve(tiles);

        formatCpp::print("Boolean value after graph solved! {}\n",  isSolved);
    }

    // This is just to reset the grid to their iniital colors.
    void clear(){
        for(size_t row = 0; row < tiles.size(); row++){
            for(size_t col = 0; col < tiles[0].size(); col++){
                tiles[row][col].setFillColor(sf::Color::White);
            }
        }
    }

    void draw(sf::RenderWindow* window){
        if(isSolved){
            for(size_t row = 0; row < tiles.size()/2; row++){
                for(size_t col = 0; col < tiles[0].size()/2; col++){
                    window->draw(tiles[row][col]);
                }
            }
            return;
        }
        for(size_t row = 0; row < tiles.size()/2; row++){
            for(size_t col = 0; col < tiles[0].size()/2; col++){
                window->draw(tiles[row][col]);
            }
        }
    }

    void resetVal(bool val){
        isSolved = val;
    }

    friend std::ostream& operator<<(std::ostream& outs, const Map& other){
        return outs << formatCpp::format("width: {}, height: {}\n", other.tiles.size(), other.tiles[0].size());
    }

    
    std::vector<sf::RectangleShape>& operator[](int index){
        return tiles[index];
    }

private:
    std::vector<std::vector<sf::RectangleShape> > tiles; // each row creating a small square (essentially the idea.)
    sf::Vector2f cellSize;
    bool isSolved;

    
};