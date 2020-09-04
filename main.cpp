#include "factorio.hpp"





int main()
{

    sf::RenderWindow window(sf::VideoMode(1000, 500), "SFML");

    auto s = window.getSize();
    width = s.x;
    height = s.y;

    PerlinNoise p = PerlinNoise(rand());
    
    World w(rand());

    Perspective = View(FloatRect(0.f, 0.f, s.x, s.y));
    window.setView(Perspective);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

          
            if (event.type == sf::Event::MouseWheelMoved){
          
          
                Perspective.setSize(width,height);
                zoom+=event.mouseWheel.delta*ZOOM_FACTOR;
                if(zoom<=1){
                    zoom = 1;
                }
                Perspective.zoom(zoom);
          
          
          
          
            }
        }

        //Perspective.zoom(zoom);
        Perspective.setCenter(width/2,height/2);
        window.setView(Perspective);
        window.clear();

        


        window.display();
    }

    return 0;
}