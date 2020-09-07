#include "factorio.hpp"

UXContext context2;
UXContext context;
Button b2(&context2, 500,500,200,200);
Button b;

void print_nonsense(UXElement* beans, void*n){
    //something

    //cout << "RESPONSE: Button" << endl;
    beans->show();
}


void switch_back(UXElement* a, void*n){


}
void animationFinished(UXElement* a, void*n){
    cout << a << endl;
}



void dosomething(UXElement* a, void*n){
    //cout << "RESPONSE: [text]" << endl;
    b.show();
}

int main()
{

    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(1000,1000), "SFML");

    loadAllAssets();


    TextNode templte;
    templte.size = 15;
    templte.styles = Text::Underlined;

    TextNode default_label;
    default_label.styles = Text::Bold;
    default_label.colors[CI_FILL] = Color(255,255,255);
    default_label.colors[CI_BORDER] = Color(0,0,0);
    default_label.outlineThickness = 2;



    b.create(&context,0,500,100,100);
    b.setColor(CI_FILL, Color(255,0,255));
    b.setTextNode(TextNode(templte, "Button"));
    b.pre_render();
    b.setEvent(print_nonsense);
    b.setAnimation(A_SHOW, new UXAnimations::Fade(1000,animationFinished));
    b.hide();
    b.ID = 0;


    Button second(&context, 500,500,100,100);
    second.setImage(Tiles::s_blank);
    second.setColor(CI_FILL, _UX_NOMASK);
    second.pre_render();
    second.setEvent(dosomething);



    Label l(&context,TextNode(default_label, "This is a label. "),100,700);
    l.pre_render();

    context.activate();

    b2.pre_render();
    b2.setEvent(switch_back);




    auto s = window.getSize();
    width = s.x;
    height = s.y;





    Animation blank = Tiles::an_belt1;
    
    




    Perspective = View(FloatRect(0.f, 0.f, s.x, s.y));
    window.setView(Perspective);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            UX::feedUXEvent(event);
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
        
        
        
        UX::requestUXFrame(&window);
        window.display();
    }

    return 0;
}