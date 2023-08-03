#pragma once
#include <formatCpp/formatCpp.h>
#include <SFML/Graphics.hpp>

// Will use this to create buttons for the UI
/**
 * @brief 
 * 
 * Button
 * Button(width, height, title)
 * 
 * -- features --
 * button.setText()
 * button.setPosition();
 * button.draw(window);
 * button.setFont(font); // this is to set the font for the text (also bounds-check if the font initialized)
 * 
 * 
*/
class Button{
public:
    Button(int width, int height, std::string title){}

    bool buttonPressed(){}

    void setText(const std::string text){
        this->text.setString(text);
    }
    void setCharacterSize(int val){ text.setCharacterSize(val); }

    void draw(sf::RenderWindow* window){}
private:
    sf::RectangleShape shape;
    sf::Font font;
    sf::Color color;
    sf::Text text;
};