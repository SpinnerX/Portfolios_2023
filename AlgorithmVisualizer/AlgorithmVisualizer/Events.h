#pragma once
#include <SFML/Graphics.hpp>
// #include <map> // use this to have a hash table of keys
#include <unordered_map>
#include <formatCpp/formatCpp.h>

class Events{
public:
    static void listener(sf::RenderWindow* window, sf::Event& event){
        instance = new Events();
        instance->event = event;
        while(window->pollEvent(instance->event)){}
    }

    /*
    static void insertKey(sf::Keyboard& key, const std::string&& value){
        // instance->keysDatabase.insert({key, value});
        // instance->keysDatabase[key] = value;
    }
    */

   // Checking if the keys are being handled when being clicked!
    static std::string keys(){
        
        if(instance->event.type == sf::Event::KeyPressed){
            formatCpp::print("Keys function called\n");
            if(instance->event.key.code == sf::Keyboard::W) return "W";
            if(instance->event.key.code == sf::Keyboard::E) return "E";
            if(instance->event.key.code == sf::Keyboard::Escape) return "Escape";
            // if(keysDatabase.count(instance->event.key.code)) return keysDatabase[instance->event.key.code];
        }

        return "Default";
    }

    static std::string mouse(){

        // Testing to see if we catch the event of a button being pressed
        if(instance->event.type == sf::Event::MouseButtonPressed){
            formatCpp::print("Mouse function called\n");
            if(instance->event.mouseButton.button == sf::Mouse::Right) return "Mouse Right";
            if(instance->event.mouseButton.button == sf::Mouse::Left) return "Mouse Left";
        }

        return "Mouse Default";
    }

private:
    static Events* instance;
    sf::Event event;
    // std::unordered_map<sf::Keyboard, std::string> keysDatabase; // handles keys
};

Events* Events::instance;