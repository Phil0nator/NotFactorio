#include <chrono>
using namespace std::chrono;

long now(){
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

class Asset{

    public:

        virtual void draw(RenderTarget* dest) = 0;
        virtual Sprite* get() = 0;


};

class Single : public Asset{


    public:
        Sprite drawer;


        Single(){}

        Single(Sprite t, IntRect r){
            drawer=t;
            drawer.setTextureRect(r);
        }

        Sprite* get(){
            return &drawer;
        }

        void draw(RenderTarget *dest){

            dest->draw(drawer);

        }

};


class Animation : public Asset{

    private:
        Sprite drawer;
        Texture buffer;

        int idx = 0;
        long last = now();
        int frames = 0;

    public:


        Animation(string path, size_t frames){
            buffer.loadFromFile(path.c_str());
            buffer.setRepeated(true);
            drawer.setTexture(buffer);
            drawer.setTextureRect(IntRect(0,0,ASSET_DIM,ASSET_DIM));
            this->frames=frames;
        }

        void advance(){
            idx++;
            
            drawer.setTextureRect(IntRect(idx*ASSET_DIM,0,ASSET_DIM,ASSET_DIM));
            last = now();

        }

        void draw(RenderTarget *dest){

            if(now()-last > ANIMDEL){
                advance();
            }

            dest->draw(drawer);

        }

        




        Sprite* get(){

            return &drawer;

        }










};