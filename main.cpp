//
//  main.cpp
//  ццц
//
//  Created by ПК on 07.07.2021.
//

#include <iostream>
#include <SFML/Graphics.hpp>
//#include "menu.cpp"
using namespace std;
using namespace sf;

int main() {
    RenderWindow window(VideoMode(1024, 1024), "TETRIS");
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent( event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear(Color::White);
        window.display();
    }
    return 0;
}
