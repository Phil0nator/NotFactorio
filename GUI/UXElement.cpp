

void UXElement::setColor(ColorIdentifier n, Color c){

    colors[n] = c;

}

void UXElement::setEvent(UXEventCallback cb, void* extra){
    event = {this,cb,nullptr};
}