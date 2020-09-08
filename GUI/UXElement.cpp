

void UXElement::setColor(ColorIdentifier n, Color c){

    colors[n] = c;

}

void UXElement::setEvent(UXEventCallback cb, void* extra){
    event = {this,cb,extra};
    
}
bool UXElement::contains(int ix, int iy){
    return (ix>x&&ix<x+w&&iy>y&&iy<y+h);
}

void UXElement::setBorderWidth(int bw){
    borderWidth=bw;
}

void UXElement::toggle(){
    visible=!visible;
}
void UXElement::hide(){
    visible=false;
}
void UXElement::show(){
    visible=true;
    animating=true;
    for(int i = 0 ; i < 5;i++){
        if(anims[i] != nullptr){
            anims[state]->ensureCompletion(this);

            anims[i]->progress=-1;
            anims[i]->feedInitial(this);
        }
    }
}

Color UXElement::getColor(ColorIdentifier n){
    return colors[n];
}
void UXElement::setAnimation(AnimationIdentifier id, UXAnimations::Animation* anim){

    anims[id]=anim;
    anim->feedInitial(this);

}

void UXElement::handleOwnAnimation(){

    if(!animating)return;
    if(anims[state] == nullptr){
        animating=false;    
        return;
    };
    anims[state]->apply(this,state);
    if(!animating){
        context->events.enqueue(anims[state]->onfinish);
        anims[state]->ensureCompletion(this);
    }

}

void UXElement::moveToTop(){

    context->moveElementToTop(this);

}
void UXElement::moveToBottom(){

    context->moveElementToBottom(this);

}