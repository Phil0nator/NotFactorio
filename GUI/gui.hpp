



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

    /////////////////////////////////////////////////
    /// 
    /// Default Sprite-Buffer rects for tri-state elements
    /// \see Button
    /////////////////////////////////////////////////
    #define TRISTATE_BUFF_1 IntRect(0,0,w,h)
    #define TRISTATE_BUFF_2 IntRect(w,0,w,h)
    #define TRISTATE_BUFF_3 IntRect(w+w,0,w,h)

    /////////////////////////////////////////////////////////
    ///
    /// Default Colors
    ///
    /////////////////////////////////////////////////////////
    #define _UX_DEFAULT_NORMALFILL          Color(100,100,200)
    #define _UX_DEFAULT_NORMALBORDER        Color(0,0,0)
    #define _UX_DEFAULT_MOVERFILL           Color(155,155,255)
    #define _UX_DEFAULT_MOVERBORDER         Color(100,100,255)
    #define _UX_DEFAULT_MDOWNFILL           Color(200,200,255)
    #define _UX_DEFAULT_MDOWNBORDER         Color(255,255,255)
    #define _UX_DEFAULT_TEXTCOLOR           Color(200,200,200)

    ///Size of event queue
    #define __UX_EVENTQUEUESIZE 4096

    ///Default text size (px)
    #define _UX_DEFAULTTEXTSIZE 20
    #define _UX_DEFAULTTEXTNODE "[Text]"
    #define _UX_DEFAULTOUTLINETEXTSIZE 0
    #define _UX_DEFAULTFONT sf::Font::GetDefaultFont()


    #define _UX_TRANSPARENT Color(255,255,255,0)


    ////////////////////////////////////
    ///
    /// Types of elements
    ///
    ////////////////////////////////////
    enum UXType{
        UX_BUTTON, UX_ENTRY, UX_CHECK, UX_SLIDER, UX_DRAGDROP, UX_PAGE
    };

    ////////////////////////////////////////
    ///
    /// Possible states for an element to be in
    ///
    ///////////////////////////////////////
    enum UXState{
        UX_NORMAL = 0, UX_HOVER = 1, UX_ACTIVE = 2, UX_DISABLED = -1
    };

    ///////////////////////////////////////
    ///
    /// Used to change colors of elements.
    /// Use one of the following which color you will alter.
    /// \see UXElement::setColor
    ///
    ///
    /////////////////////////////////////////
    enum ColorIdentifier{

        CI_BORDER = 0, CI_FILL = 1,CI_MOVERBORDER = 2, CI_MOVERFILL = 3, CI_MDOWN_BORDER = 4, CI_MDOWN_FILL = 5,
        

    };

    
    namespace Align{
        
        ////////////////////////////////////
        ///
        /// TextAlign is an enumeration of different
        ///     ways to align text based on a container.
        ///
        /// (CENTER can not be combined with any other enum)
        ///////////////////////////////////
        enum TextAlign{

            CENTER = 1 << 31, //Non-Combinable
            LEFT   = 1 << 1,
            RIGHT  = 1 << 2,
            BOTTOM = 1 << 3,
            TOP    = 1 << 4,

        };
    }
    /// integer representation of combined Align::TextAlign enums
    typedef int Alignment;
    
    ///Forward Declaration
    class UXElement;



    ///Forward Declaration
    class UXContext;




    /// Callback Function type including pointer to caller, and additional arguments
    typedef void (*UXEventCallback)(UXElement*, void*);






    ///////////////////////////////////////////////
    ///
    /// UXEvent
    /// Used to specify a callback function, and its arguments.
    ///
    /// UXEvents are constructed internally, 
    ///         so you don't need to touch them normally
    ///
    ///
    ///
    ///
    ///
    ////////////////////////////////////////////////
    struct UXEvent
    {

        UXElement           *source;

        UXEventCallback     cb = nullptr;

        void                *extra_arg;

        void go(){
            if(cb==nullptr)return;
            cb(source,extra_arg);

        }

    };
    
    
    
    ///Forward Declaration
    void UXContext_tickthreadmainlp(UXContext *context);
    
    
    ///////////////////////////////////////////////////
    ///
    /// TextNodes are used to represent portions of text
    ///     to be displayed by UXElements.
    ///
    /// TextNodes contain the actual string content, and all
    ///     of its formatting.
    ///
    ///////////////////////////////////////////////////
    struct TextNode{

        ///Actual string content
        string content = _UX_DEFAULTTEXTNODE;
        
        ///\see sf::Font
        /// defaults to arial.ttf
        sf::Font font;

        ///Text size (px)
        int size = _UX_DEFAULTTEXTSIZE;

        ///BorderWidth (px)
        int outlineThickness =_UX_DEFAULTOUTLINETEXTSIZE;
        
        ///Color id's
        /// \see ColorIdentifier
        Color colors[2] = {_UX_DEFAULT_TEXTCOLOR, Color(0,0,0)};
        
        ///Styling
        /// \see sf::Text::Style
        sf::Text::Style styles = sf::Text::Regular;
        
        ///Text buffer object
        ///\see sf::Text
        sf::Text buffer;

        ///Alignment info
        /// \see UX::TextAlign
        Alignment ta = Align::CENTER;

        TextNode(){
            font.loadFromFile("GUI/arial.ttf");
        }

        TextNode(Font f, string t);

        TextNode(TextNode other, string newtext);


        void render();

        void draw_to(RenderTarget* target, UXElement* source, Vector2i translation);



    };






    
    
    ////////////////////////////////////////////////
    ///
    /// There can only be one active context at one time,
    ///         This will point to it.
    ///
    ////////////////////////////////////////////////
    UXContext *activeContext = nullptr;
    
    
    
    
    //////////////////////////////////////////
    ///
    /// UXContext is used to store a set of ux-elements that 
    ///             are in some way related, in order to better
    ///             optimize larger ux-schemes
    ///
    /// The UXContext will handle drawing, logic, event-resolution, and multithreading. 
    ///
    //////////////////////////////////////////
    class UXContext{
        private:
            vector<UXElement*>          elems;
            vector<sf::Event>           sfeventstack;
            Thread                      *t = new Thread(UXContext_tickthreadmainlp, this);
            bool                        active;


            
            void fillInfo();
            void cleanup();



        public:
            ///Used Internally
            Queue<UXEvent>              events = Queue<UXEvent>(__UX_EVENTQUEUESIZE);
            
            ///Mouse Coords
            int mx, my;
            ///Mouse buttons pressed, using sf::Mouse::<> as indexes
            bool mouseDowns[3] = {false,false,false};
            ///Mouse buttons released, using sf::Mouse::<> as indexes
            bool mouseUps[3] = {false,false,false};





            UXContext();
            UXContext(const UXContext& other);
            ~UXContext();

            ///Used internally
            void pushnextelement(UXElement *n);
            ///Used internally
            void texec();


            ///Set a context to be active
            ///Warning: if you activate one context before another has finished resolving its events,
            ///             those events will never be satisfied, and will be overwritten in memory.
            void activate();


            
            
            ///Accessor
            bool isActive();

            //////////////////
            /// USED INTERNALLY
            //////////////////
            void draw(RenderTarget *target);
            
            
            ///////////////////
            /// USED INTERNALLY
            ///////////////////
            void feedEvent(sf::Event e);


            ///Used internally
            vector<Event> accessSFEvents(){
                return sfeventstack;
            }
            ///Get mouse coords for ui purposes
            void accessMouseCoords(int *x, int *y);

    };

    /////////////////////////////////////////////
    ///
    /// The requestUXFrame function is used to call
    ///     mainthread functions of the active context.
    ///
    /// requestUXFrame must be called in your mainloop
    ///     where you want the UI frame to be drawn.
    ///
    /// If there is no active UXContext, the function
    ///     will return immediately.
    ///
    /////////////////////////////////////////////
    void requestUXFrame(RenderTarget *target);


    
    /////////////////////////////////////////////
    ///
    /// The feedUXEvent function is used to pass sf::Events
    ///     into the active context.
    ///
    /// feedUXEvent must be called in the eventloop of
    ///     your program, and must be passed every event
    ///     polled from the window.
    ///
    /// The events you pass into this function will still be
    ///     safe to reference after.
    ///
    /// If there is no active UXContext the function
    ///     will return immediately.
    ///
    /////////////////////////////////////////////
    void feedUXEvent(Event e);

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
            Texture buffer;
            Sprite sprtbuff[3]; //normal, mouse over, mouse down buffers for elements using images


            bool contains(int ix, int iy);
            int borderWidth = 1;





        public:
            UXState state =             UX_NORMAL;
            bool border   =             false;
            bool image    =             false;
            UXType type;
            int x, y, w, h;
            int ID;
            UXElement() = default;
            UXElement(UXContext *_context, UXType _type){
                type=_type;
                
                context=_context;
                context->pushnextelement(this);
            }

            void setColor(ColorIdentifier n, Color c);
            void setBorderWidth(int bw);
        
            void setEvent(UXEventCallback cb, void* extra = nullptr);
            virtual void redraw(RenderTarget* dest) = 0;
            virtual void pre_render() = 0;
            virtual void logic() = 0;


    };

    #include "UXElement.cpp"


    class Button : public UXElement{
        Sprite      imbf;
        TextNode    text;
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
            void setTextNode(TextNode t);


    };

    #include "Button.cpp"
    #include "TextNode.cpp"
    #include "UXContext.cpp"

    



    



}



#endif


