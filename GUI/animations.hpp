


class UXAnimations::Fade : public UXAnimations::Animation{
    Color finish;
    Color current;
    int sp = 0;
    public:
    Fade(int duration, UXEventCallback onfinish = nullptr) : UXAnimations::Animation(){

        this->duration=duration;
        this->onfinish.cb=onfinish;
        timepertick = ceil(duration/255);

    }

    void feedInitial(UXElement* og){
        finish=og->getColor(CI_FILL);
        Color newstart = Color(finish);
        newstart.a=0;
        current=newstart;
        og->setColor(CI_FILL, newstart);
        this->onfinish.source=og;

    }
    void ensureCompletion(UXElement* og){
        current.a=255;
        og->sprtbuff[sp].setColor(current);

    }

    void apply(UXElement* dest, int sprite){

        sp = sprite;
        if(progress==-1){
            progress=0;
            last = millis();
            
        }else if (millis()-last < timepertick){
            return;
        }
        last = millis();
        if(progress == 255){
            dest->animating=false;
            return;
        }
        progress++;
        current.a+=1;
        dest->sprtbuff[sprite].setColor(current);

    }


};




class UXAnimations::Swipe : public UXAnimations::Animation{

    Vector2i finish;
    Vector2i current;
    Direction dir = UP;
    public:
    int dist;

    Swipe(int duration, Direction direction, int distance,UXEventCallback onfinish = nullptr) : UXAnimations::Animation(){
        this->duration=duration;
        this->onfinish.cb=onfinish;
        dir=direction;
        dist=distance;
        timepertick = duration / (pow(dist,0.25));

    }

    void ensureCompletion(UXElement* og){

        og->x = finish.x;
        og->y = finish.y;

    }

    void feedInitial(UXElement* og){

        this->onfinish.source = og;
        finish.x = og->x;
        finish.y = og->y;
        current.x=finish.x;
        current.y=finish.y;
        switch(dir){

            case UP:
                current.y+=dist;
                velocity.y = -1;
                break;
            case DOWN:
                current.y-=dist;
                velocity.y=1;
                break;
            case LEFT:
                current.x+=dist;
                velocity.x=-1;
                break;
            case RIGHT:
                current.x-=dist;
                velocity.x=1;
                break;

        }

        
    }

    void apply(UXElement* dest, int sprite){


        if(progress==-1){
            progress=0;
            last = millis();
            
        }else if (millis()-last < timepertick){
            return;
        }
        last = millis();
        if(abs(velocity.x+velocity.y) < 1){
            dest->animating=false;
            return;
        }
        progress++;


        if(current.x>finish.x){
            velocity.x=-(current.x-finish.x)/4;
        }else if (current.x < finish.x){
            velocity.x=-(current.x-finish.x)/4;
        }




        if(current.y > finish.y){
            velocity.y=-(current.y-finish.y)/4;
        }
        else if (current.y < finish.y){
            velocity.y=-(current.y-finish.y)/4;
        }

        current+=velocity;
        dest->x = current.x;
        dest->y = current.y;


    }


};


class UXAnimations::Wiggle : public UXAnimations::Animation{




};