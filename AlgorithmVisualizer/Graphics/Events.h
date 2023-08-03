#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map> // use this to have a hash table of keys
#include <formatCpp/formatCpp.h>
#include "common.h" // so we can call EnumClassHash: class

class Events{
public:
    Events(sf::RenderWindow* window) : window(window) {}
    
    ~Events(){
        _key = "";
        _mouse = "";
        delete window;
    }

    static void Initialize(sf::RenderWindow* window){
        instance = new Events(window); // we must initialize the class so we dont get seg fault...
    }

    
    static void insert(sf::Keyboard::Key key, std::string value){
        instance->keysDatabase.insert({key, value});
    }

    static void insertMouse(sf::Mouse::Button button, std::string value){
        instance->mouseDatabase.insert({button, value});
    }

    static void setMouseRepeatEnabled(bool val){
        instance->mouseRepeat = val;
    }
    

    static void listener(){
        instance->reset();


        while(instance->window->pollEvent(instance->event)){
            if(instance->event.type == sf::Event::Closed) instance->window->close();

            // checking key/mouse events are being handled correctly.
            if(instance->event.type == sf::Event::KeyPressed){
                instance->_key = instance->getKey(instance->event);
            }

            
            if(instance->event.type == sf::Event::MouseButtonPressed){
                instance->_mouse = instance->getMouse(instance->event);
            }
        }
    }

    static bool isFocused() { return instance->isFocusedEnabled; }

    static void setFocusedEnabled(bool val){
        instance->isFocusedEnabled = val;
    }

    static std::string keys(){ return instance->_key; }

    static std::string mouse() { return instance->_mouse; }

private:
    std::string getKey(sf::Event& event){
        // bounds checking.
        if(keysDatabase.size() <= 0){
            formatCpp::print("Need to insert keys into keyDatabase - size 0\n");
            exit(0);
        }

        // We use hash table to find specific keys, to allow an easier handler to check what keys are available in the constructor.
        if(keysDatabase.contains(event.key.code)) return keysDatabase[event.key.code];
        return "Key not found in hashtable.";
    }

    std::string getMouse(sf::Event& event){
        // bounds checking
        if(mouseDatabase.size() <= 0){
            formatCpp::print("Need to insert mouse into mouseDatabase - size 0\n");
            exit(0);
        }

        if(mouseDatabase.contains(event.mouseButton.button)) return mouseDatabase[event.mouseButton.button];

        return "Mouse not found in hashtable.";
    }

    // Reset so that key and mouse events aren't falsly handling key/mouse events
    void reset(){
        if(!mouseRepeat){
            resetMouse();
        }
        
        resetKey();
    }

    void resetMouse(){
        _mouse = "";
    }

    void resetKey(){
        _key = "";
    }

private:
    static Events* instance;
    sf::RenderWindow* window;
    sf::Event event;
    std::unordered_map<sf::Keyboard::Key, std::string, EnumClassHash> keysDatabase; // handles keys
    std::unordered_map<sf::Mouse::Button, std::string, EnumClassHash> mouseDatabase; // handle mouse events
    std::string _key;
    std::string _mouse;
    bool mouseRepeat; // this allow sus to repeatedly let the mouse to click.
    bool isFocusedEnabled;
};

Events* Events::instance;