#include "factorio.hpp"



void print_nonsense(UXElement* beans, void*n){
    cout << "stuff"<<rand() << endl;
}

int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(1000,1000), "SFML");

    UXContext context;
    Button b(&context,0,500,100,100);
    b.setColor(CI_FILL, Color(255,0,255));
    b.pre_render();
    b.setEvent(print_nonsense);
    context.activate();


    auto s = window.getSize();
    width = s.x;
    height = s.y;




    loadAllAssets();

    Animation blank = Tiles::an_belt1;
    
    




    Perspective = View(FloatRect(0.f, 0.f, s.x, s.y));
    window.setView(Perspective);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            context.feedEvent(event);
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


        CircleShape s(100);
        s.setPosition(0,0);
        blank.get()->setPosition(0,0);
        blank.draw(&window);
        Tiles::get(BLANK)->get()->setPosition(ASSET_DIM,0);
        Tiles::get(BLANK)->draw(&window);
        context.draw(&window);

        window.display();
    }

    return 0;
}