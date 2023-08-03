#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <unordered_set>
#include "Graphics/common.h"
#include <formatCpp/formatCpp.h>

struct Tile{
    Tile() = delete;
    Tile(int x, int y, int from_x, int from_y, double distance) {
		this->x = x;
		this->y = y;
		this->from_x = from_x; //-1 if the start tile
		this->from_y = from_y; //-1 if the start tile
		this->distance = distance;
	}

    friend std::ostream& operator<<(std::ostream& outs, const Tile& t){
        return outs << formatCpp::format("x = {}, y = {}, from_x = {}, from_y = {}, distance = {}\n", t.x, t.y, t.from_x, t.from_y, t.distance);
    }

    bool operator==(const Tile& other) const{
        return (x == other.x and y == other.y);
    }

    bool operator<(Tile& rhs) const { 
        return distance < rhs.distance;
    }

    int x;
    int y;
    int from_x, from_y; // previous locations that we came from.
    double distance; // used for Dijkstras. Distance from starting (terms by walking)
};

// Comparison function to make a min heap instead of max heap of tiles
// Make min heap like: priority_queue<Tile, std::vector<Tile>, Tile_Comp> pathQueue;
struct Tile_Comp{
    bool operator()(const Tile& lhs, const Tile& rhs){
        return lhs.distance > rhs.distance;
    }
};


namespace std {
    template<> struct hash<Tile>{
        size_t operator()(const Tile& t) const {
            return 1000 * (size_t)t.x + (size_t)t.y;
        }
    };
};