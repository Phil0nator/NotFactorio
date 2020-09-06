

void UXContext::pushnextelement(UXElement* n){
    elems.push_back(n);
}

void UXContext::texec(){
    while (events.empty()){} // wait for new stuff
    UXEvent e = events.dequeue();
    cout << events.count << endl;
    e.go();
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


void UXContext::activate(){
    if(activeContext == nullptr){
        activeContext = this;
    }else{
        activeContext->active = false;
        activeContext = this;
    }
    active = true;
    t->launch();
}
void UXContext::feedEvent(sf::Event e){

    sf::Event cpy = sf::Event(e);
    sfeventstack.push_back(cpy);

}

void UXContext::draw(RenderTarget* dest){

    fillInfo();

    for(int i = 0 ; i < elems.size();i++){
        elems.at(i)->logic();
        elems.at(i)->redraw(dest);
    }


    sfeventstack.clear();


}