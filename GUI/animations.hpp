
namespace UXAnimations{

    class Fade : public Animation{
        Color finish;
        Color current;

        public:
        Fade(int duration, UXEventCallback onfinish = nullptr) : Animation(){

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

        void apply(UXElement* dest, int sprite){

            
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

    


}