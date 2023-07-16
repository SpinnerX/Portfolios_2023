#pragma once
#include <SFML/Graphics.hpp>
#include "Events.h"
#include <iostream>

class Window{
    Window(int w, int h, const std::string& title, sf::Uint32 style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings()){
        window = new sf::RenderWindow();
        window->create(sf::VideoMode(w, h), title, style, settings);
        // Events::insertKey(sf::Keyboard::W, "W");
        // Events::insertKey(sf::Keyboard::E, "E");
    }

public:
    static Window* create(int w, int h, const std::string& title){
        return new Window(w, h, title);
    }

    void mainloop(){
        while(window->isOpen()){
            Events::listener(window, event);
            if(Events::keys() == "Escape") window->close();

            if(Events::mouse() == "Mouse Right") formatCpp::print("Mouse Right Pressed!\n");
            if(Events::mouse() == "Mouse Left") formatCpp::print("Mouse Left Pressed!\n");

            window->display();
        }
    }

    void drawingSquareShape(){
        sf::RectangleShape testingTile;
        testingTile.setSize(sf::Vector2f(30, 30));
        testingTile.setFillColor(sf::Color::Green);
        testingTile.setOutlineThickness(0.5f);
        testingTile.setOutlineColor(sf::Color::Black);
        testingTile.setPosition(0, 0);
        window->draw(testingTile);
    }

private:
    sf::RenderWindow* window;
    sf::Event event;
};

