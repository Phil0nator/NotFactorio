

void UXContext::pushnextelement(UXElement* n){
    elems.push_back(n);
}

void UXContext::texec(){


    while (events.empty()){} // wait for new stuff
    UXEvent e;
    if(events.dequeue(&e)){
        e.go();
    }
    

    
}

void UXContext_tickthreadmainlp(UXContext *context){
    while(context->isActive()){
        context->texec();
    }
}
UXContext::UXContext(const UXContext& other){
    elems = other.elems;
    events.ld(other.events);
    active = other.active;
}

UXContext::~UXContext(){
    delete t;
}

UXContext::UXContext(){

    active = false;

}

bool UXContext::isActive(){

    return active;

}
void UXContext::cleanup(){

    t->terminate();
    active=false;
    events.reset();
    sfeventstack.clear();
    fillInfo();

}

void UXContext::activate(){
    if(activeContext == nullptr){
        activeContext = this;
        active = true;
        t->launch();
        return;
    }

    UXContext *old = activeContext;
    activeContext = this;
    sfeventstack = old->sfeventstack;
    active = true;
    t->launch();
    old->cleanup();
}
void UXContext::feedEvent(sf::Event e){

    sf::Event cpy = sf::Event(e);
    sfeventstack.push_back(cpy);

}

void UXContext::draw(RenderTarget* dest){

    fillInfo();

    for(int i = 0 ; i < elems.size();i++){
        if(!elems.at(i)->visible)continue;
        elems.at(i)->handleOwnAnimation();
        elems.at(i)->logic();
        elems.at(i)->redraw(dest);
    }


    sfeventstack.clear();


}


void UXContext::accessMouseCoords(int *x, int *y){

    *x = mx;
    *y = my;

}


void UXContext::fillInfo(){

    mouseUps[0]=mouseUps[1]=mouseUps[2]=false;
    for (int i = 0 ; i < sfeventstack.size();i++){
        Event e = sfeventstack.at(i);
        if (e.type == sf::Event::Closed){
            t->terminate();
        }
        if(e.type == Event::MouseMoved){
            mx = e.mouseMove.x;
            my = e.mouseMove.y;
            sfeventstack.erase(sfeventstack.begin()+i);
        }else if (e.type == Event::MouseButtonPressed){
            
            mouseDowns[e.mouseButton.button] = true;
            sfeventstack.erase(sfeventstack.begin()+i);

        }else if (e.type == Event::MouseButtonReleased){

            mouseDowns[e.mouseButton.button]=false;
            mouseUps[e.mouseButton.button]=true;
            sfeventstack.erase(sfeventstack.begin()+i);

        }
    }

}


void requestUXFrame(RenderTarget *target){
    if(activeContext == nullptr)return;

    View v = target->getView();
    target->setView(target->getDefaultView());
    activeContext->draw(target);
    target->setView(v);

}

void feedUXEvent(Event e){

    if(activeContext == nullptr)return;
    activeContext->feedEvent(e);
}

void UXContext::moveElementToTop(UXElement*ptr){

    for(int i = 0 ; i < elems.size();i++){
        if(elems.at(i) == ptr){
            elems.erase(elems.begin()+i);
        }
    }

    elems.push_back(ptr);

}

void UXContext::moveElementToBottom(UXElement*ptr){
    for(int i = 0 ; i < elems.size();i++){
        if(elems.at(i) == ptr){
            elems.erase(elems.begin()+i);
        }
    }
    elems.insert(elems.begin(),ptr);
}