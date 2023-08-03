#include "Window.h"

int main(){
    Window::create( sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height, "Algorithm Visualizer")->mainloop();
}