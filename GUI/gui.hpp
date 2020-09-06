#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include "Queue.hpp"
#include <string>
#include <thread>

#ifndef __GUI__
#define __GUI__


namespace UX{


    using namespace sf;
    using namespace std;


    #define TRISTATE_BUFF_1 IntRect(0,0,w,h)
    #define TRISTATE_BUFF_2 IntRect(w,0,w,h)
    #define TRISTATE_BUFF_3 IntRect(w+w,0,w,h)


    #define _UX_DEFAULT_NORMALFILL          Color(100,100,200)
    #define _UX_DEFAULT_NORMALBORDER        Color(0,0,0)
    #define _UX_DEFAULT_MOVERFILL           Color(155,155,255)
    #define _UX_DEFAULT_MOVERBORDER         Color(100,100,255)
    #define _UX_DEFAULT_MDOWNFILL           Color(200,200,255)
    #define _UX_DEFAULT_MDOWNBORDER         Color(255,255,255)





    #define __UXENTRY__


    enum UXType{
        UX_BUTTON, UX_ENTRY, UX_CHECK, UX_SLIDER, UX_DRAGDROP, UX_PAGE
    };

    enum UXState{
        UX_NORMAL = 0, UX_HOVER = 1, UX_ACTIVE = 2, UX_DISABLED = -1
    };


    enum ColorIdentifier{

        CI_BORDER = 0, CI_FILL = 1,CI_MOVERBORDER = 2, CI_MOVERFILL = 3, CI_MDOWN_BORDER = 4, CI_MDOWN_FILL = 5

    };

    class UXElement;




    class UXContext;





    typedef void (*UXEventCallback)(UXElement*, void*);







    struct UXEvent
    {

        UXElement           *source;

        UXEventCallback     cb;

        void                *extra_arg;

        void go(){

            cb(source,extra_arg);

        }

    };
    
    
    
    
    void UXContext_tickthreadmainlp(UXContext *context);
    
    
    
    
    
    
    UXContext *activeContext = nullptr;
    
    
    
    
    
    class UXContext{
        private:
            vector<UXElement*>          elems;
            vector<sf::Event>           sfeventstack;
            Thread                      *t = new Thread(UXContext_tickthreadmainlp, this);
            bool                        active;


            
            void fillInfo(){

                if(sfeventstack.size() == 0)return;
                
                
                mouseDown[0]=false;mouseDown[1]=false;mouseDown[2]=false;
                mouseRel[0]=false;mouseRel[1]=false;mouseRel[2]=false;

                resized =              false;
                mouseWheelDelta =      0;
                textEntered =          false;
                mouseStateChange =     false;

                while(sfeventstack.size()>0){

                    Event e = sfeventstack.at(sfeventstack.size()-1);
                    sfeventstack.pop_back();



                    switch(e.type){

                        case Event::Resized:                size = e.size;                  resized=true;                                                       break;
                        case Event::KeyPressed:             key = e.key;                    keys[e.key.code]=true;                                              break;
                        case Event::KeyReleased:            key = e.key;                    keys[e.key.code]=false;                                             break;
                        case Event::TextEntered:            text = e.text;                  textEntered=true;                                                   break;
                        case Event::MouseMoved:             mouseMove = e.mouseMove;                                                                            break;
                        case Event::MouseButtonPressed:     mouseButton = e.mouseButton;    mouseDown[(int)e.mouseButton.button]=mouseStateChange=true;         break;
                        case Event::MouseButtonReleased:    mouseButton = e.mouseButton;    mouseRel[(int)e.mouseButton.button]=mouseStateChange=true;          break;
                        case Event::MouseWheelMoved:        mouseWheel = e.mouseWheel;      mouseWheelDelta=e.mouseWheel.delta;                                 break;


                    }
                    
                    

                }

            }



        public:

            Queue<UXEvent>              events = Queue<UXEvent>(4096);


            ////////////////////////////////////////////
            /// Union contents copied directly from sf::Event in order to store all event info for a context
            /// (Excludes Joystick, sensor, and other events for relevancy)
            /// @see sf::Event  
            ////////////////////////////////////////////

            Event::SizeEvent             size;              ///< Size event parameters (Event::Resized)
            Event::KeyEvent              key;               ///< Key event parameters (Event::KeyPressed, Event::KeyReleased)
            Event::TextEvent             text;              ///< Text event parameters (Event::TextEntered)
            Event::MouseMoveEvent        mouseMove;         ///< Mouse move event parameters (Event::MouseMoved)
            Event::MouseButtonEvent      mouseButton;       ///< Mouse button event parameters (Event::MouseButtonPressed, Event::MouseButtonReleased)
            Event::MouseWheelEvent       mouseWheel;        ///< Mouse wheel event parameters (Event::MouseWheelMoved) (deprecated)

            bool mouseDown[3] =          {false,false,false};
            bool mouseRel[3] =           {false,false,false};
            
            bool keys                   [1024];
            bool resized =              false;
            int mouseWheelDelta =            0;
            bool textEntered =          false;
            bool mouseStateChange =     false;




            UXContext();
            UXContext(const UXContext& other);
            ~UXContext();
            void pushnextelement(UXElement *n);
            void texec();
            void activate();
            void deactivate();
            
            bool isActive();

            void draw(RenderTarget *target);
            void feedEvent(sf::Event e);

    };




    class UXElement{
        protected:
            UXElement *parent;
            UXContext *context;

            ////////////////////////////////////////////////////////
            //{
            //  NORMAL : {C,C},
            //  MOVER  : {C,C},
            //  MDOWN  : {C,C}
            //}
            ///////////////////////////////////////////////////////

            Color colors[6] = {_UX_DEFAULT_NORMALBORDER, _UX_DEFAULT_NORMALFILL, _UX_DEFAULT_MOVERBORDER, _UX_DEFAULT_MOVERFILL, _UX_DEFAULT_MDOWNBORDER,_UX_DEFAULT_MDOWNFILL};
            UXEvent event;
            string text = "UXElement";
            Texture buffer;
            Sprite sprtbuff[3]; //normal, mouse over, mouse down buffers for elements using images


            bool contains(int ix, int iy){

                return (ix>x&&ix<x+w&&iy>y&&iy<y+h);

            }






        public:
            UXState state =             UX_NORMAL;
            bool border   =             false;
            bool image    =             false;
            UXType type;
            int x, y, w, h;
            UXElement() = default;
            UXElement(UXContext *_context, UXType _type){
                type=_type;
                
                context=_context;
                context->pushnextelement(this);
            }

            void setColor(ColorIdentifier n, Color c);
        
            void setEvent(UXEventCallback cb, void* extra = nullptr);
            virtual void redraw(RenderTarget* dest) = 0;
            virtual void pre_render() = 0;
            virtual void logic() = 0;
            


    };

    #include "UXElement.cpp"


    class Button : public UXElement{
        Sprite      imbf;
        friend      UXContext;

        public:
            RenderTexture rt; //drawing buffer
            Button(UXContext *_context, int _x, int _y, int _w, int _h) : UXElement(_context, UX_BUTTON){
                x=_x;
                y=_y;
                w=_w;
                h=_h;
                image=false;
            }
            
            void setImage(Sprite tx);
            void redraw(RenderTarget* dest);
            void pre_render();
            void logic();


    };

    #include "Button.cpp"




    #include "UXContext.cpp"

    



    



}



#endif


