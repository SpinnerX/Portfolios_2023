#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <formatCpp/ofstream.h>
#include <formatCpp/containers.h>
#include "Graphics/Events.h"
#include "Map.h"
#include <queue> // FIFO - for coloring our starting and ending points.
#include <vector>
#include "Graphics/Colors.h"

/**
 * @brief 
 * 
 * Features to start thinking about now. (Brain storming ideas)
 * Right-click - setting starting and ending (DONE)
 * Left-click - setting the walls  (DONE)
 * Dropdown box - list of algorithms to visualize.
 * Space - to start visualization (DONE)
 * 
 * Implementing BFS to test graph theory visualization (IN-PROGRESS)
 * 
 */

class Window{
    Window(int w, int h, const std::string& title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings()){
        window = new sf::RenderWindow();
        window->create(sf::VideoMode(w, h), title, style, settings);
        window->setFramerateLimit(60);

        // map = Map(25, 110);
        map = Map(150, 70);
        // map = Map(150, 60);
        map.generate();

        Events::Initialize(window);
        Events::insert(sf::Keyboard::Escape, "Escape");
        Events::insert(sf::Keyboard::W, "W");
        Events::insert(sf::Keyboard::D, "D");
        Events::insert(sf::Keyboard::S, "S");
        Events::insert(sf::Keyboard::A, "A");
        Events::insert(sf::Keyboard::Q, "Q");
        Events::insert(sf::Keyboard::Space, "Space");
        Events::insert(sf::Keyboard::T, "T");
        Events::insert(sf::Keyboard::BackSpace, "BackSpace");
        Events::insert(sf::Keyboard::E, "E");
        Events::insert(sf::Keyboard::N, "N");

        Events::insertMouse(sf::Mouse::Button::Left, "Mouse Left");
        Events::insertMouse(sf::Mouse::Button::Right, "Mouse Right");

        // This will draw the selector on the grid to follow the mouse
        tileSelector = sf::RectangleShape(map.cell_size());
        tileSelector.setFillColor(sf::Color::Transparent);
        tileSelector.setOutlineThickness(1.f);
        tileSelector.setOutlineColor(sf::Color::Green);

        // coordinatesColors.push(sf::Color(144, 238, 144)); // light green
        coordinatesColors.push(Colors::lightGreen); // light green
        // coordinatesColors.push(sf::Color(128, 0, 128)); // purple
        coordinatesColors.push(Colors::purple); // purple

        coordinates = std::vector<Tile>(); // to store the starting and ending points
    }

public:
    
    ~Window(){
        delete window;
    }

    static Window* create(int w, int h, const std::string& title){
        return new Window(w, h, title);
    }

    void mainloop(){
        float gridSize = 100.f;

        sf::View view;
        view.setSize(1920, 1080);
        view.setCenter(window->getSize().x/2.f, window->getSize().y/2.f);
        sf::RectangleShape shape(sf::Vector2f(gridSize, gridSize));

        sf::Clock deltatime;
        sf::Font font;
        font.loadFromFile("../Fonts/Dosis-Light.ttf");

        sf::Text text;
        text.setCharacterSize(15); // setting size of the character.
        text.setFont(font);
        text.setPosition(190.f, 890.f);
        text.setFillColor(sf::Color::Black);

        sf::Text projectTitle;
        projectTitle.setString("Algorithm Visualizer");
        projectTitle.setCharacterSize(60);
        projectTitle.setFont(font);
        projectTitle.setFillColor(sf::Color(128, 128, 128));

        // x = higher will be positioned to right more, lower positioned to the left, y = lower the more higher it'll be positioned
        projectTitle.setPosition(750.f, 5.f);


        while(window->isOpen()){
            dt = deltatime.restart().asSeconds(); // use this to implement FPS (once we get a graph theory algorithm working)
            Events::listener();

            mousePosScreen = sf::Mouse::getPosition(); // gets mouse current position
            mousePosWindow = sf::Mouse::getPosition(*window); // gets mouse current position for window
            mousePosView = window->mapPixelToCoords(mousePosWindow); // gets mouse current position for view

            std::string status = mousePositionStatus(); // this helps us to get the mouse position in the window.
            window->setView(view);
            text.setString(status);

            // Window closes when we click "Escape" key
            if(Events::keys() == "Escape") window->close();

            // Left-click to set the starting and ending points
            if(Events::mouse() == "Mouse Left"){
                Events::setMouseRepeatEnabled(false); // this allows us to drag when we click on the map to create walls.

                if(!coordinatesColors.empty()){
                    sf::Color color = coordinatesColors.front();
                    map[mousePosGrid.x][mousePosGrid.y].setFillColor(color);
                    coordinatesColors.pop();

                    
                    Tile newTile = Tile(mousePosGrid.x, mousePosGrid.y, -1, -1, -1);
                    coordinates.push_back(newTile);
                }
            }

            // right-click to set the walls onto the map.
            if(Events::mouse() == "Mouse Right"){
                Events::setMouseRepeatEnabled(true);
                // map[mousePosGrid.x][mousePosGrid.y].setFillColor(sf::Color(128, 128, 128));
                map[mousePosGrid.x][mousePosGrid.y].setFillColor(Colors::lightGrey);
            }

            // click space to start the graph visualizer
            if(Events::keys() == "Space"){
                formatCpp::print("Space Entered!\n");
                Tile starting = coordinates[0], ending = coordinates[1];
                // std::string stats = "Dijkstras";
                std::string stats = "BFS";
                map.solve(starting, ending, stats);
            }
            

            // backspace key to reset the map (possibly turn this into a buttonn feature)
            if(Events::keys() == "BackSpace") reset();

            window->clear(Colors::lightBlueCustom);
            window->setView(view);

            // rendering visualization
            window->setView(window->getDefaultView());

            window->draw(text);
            window->draw(projectTitle);

            map.draw(window);
            window->draw(tileSelector);

            window->display();
        }
    }

private:
    std::string mousePositionStatus(){
        const float offset = 5.f; // for tile selector
        // prevents any division error.
        if(mousePosView.x >= 0.f) mousePosGrid.x = mousePosView.x / static_cast<unsigned>(map.cell_size().x);
        if(mousePosView.y >= 0.f) mousePosGrid.y = mousePosView.y / static_cast<unsigned>(map.cell_size().y);

        std::stringstream ss;
        /*
        ss << "Debug Mode\n";
        ss << formatCpp::format("Screen: ({}, {})\n", mousePosScreen.x, mousePosScreen.y)
           << formatCpp::format("Window: ({}, {})\n", mousePosWindow.x, mousePosWindow.y)
           << formatCpp::format("View: ({}, {})\n", mousePosView.x, mousePosView.y)
           << formatCpp::format("Grid: ({}, {})\n", mousePosGrid.x, mousePosGrid.y)
           << formatCpp::format("FPS: {}\n", dt)
           << formatCpp::format("Coordinates Vec Size: {}\n", coordinates.size());
        */
       
       ss << "Debug Mode\n"
          << formatCpp::format("Mouse Grid: ({}, {})\n", mousePosGrid.x, mousePosGrid.y);

        unsigned int currentX = mousePosGrid.x * map.cell_size().x + offset;
        unsigned int currentY = mousePosGrid.y * map.cell_size().y + offset;

        ss << formatCpp::format("Current X = {} and Current Y: {}\n", currentX, currentY);
        
        // if(currentX <= maxTileX || currentY < maxTileY) tileSelector.setPosition(currentX, currentY);
        if(currentX < map.rows() || currentX >= map.rows() || currentY >= map.cols()) tileSelector.setPosition(currentX, currentY);

        return ss.str();
    }

    void reset(){
        map.clear();
        coordinatesColors.push(sf::Color(144, 238, 144)); // light green
        coordinatesColors.push(sf::Color(128, 0, 128)); // purple
        coordinates.clear();
        map.resetVal(false);
    }

private:
    sf::RenderWindow* window;
    Map map;

    // -- stats/debugging text
    // purpose to help debug and give information about coordinates.
    // Mouse position updates
    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2u mousePosGrid;

    float dt; // deltatime for FPS

    sf::RectangleShape tileSelector;
    std::queue<sf::Color> coordinatesColors; // FIFO - for coloring our starting and ending points.

    std::vector<Tile> coordinates; // [0] - starting, [1] = ending.
};

