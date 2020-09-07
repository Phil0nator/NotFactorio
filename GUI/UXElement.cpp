

void UXElement::setColor(ColorIdentifier n, Color c){

    colors[n] = c;

}

void UXElement::setEvent(UXEventCallback cb, void* extra){
    event = {this,cb,nullptr};
}
bool UXElement::contains(int ix, int iy){
    return (ix>x&&ix<x+w&&iy>y&&iy<y+h);
}