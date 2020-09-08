
void Panel::redraw(RenderTarget *dest){
    sprtbuff[0].setPosition(x,y);
    dest->draw(sprtbuff[0]);   
}

void Panel::logic(){

}

void Panel::pre_render(){
    buff = RectangleShape(Vector2f(w,h));
    buff.setFillColor(colors[CI_FILL]);
    RectangleShape outline = RectangleShape(Vector2f(w-borderWidth*2,h-borderWidth*2));
    outline.setFillColor(_UX_TRANSPARENT);
    outline.setOutlineColor(colors[CI_BORDER]);
    outline.setOutlineThickness(borderWidth);
    outline.setPosition(borderWidth,borderWidth);
    

    rt.create(w,h);
    rt.draw(buff);
    rt.draw(outline);

    sprtbuff[0] = sprtbuff[1] =sprtbuff[2] = Sprite(rt.getTexture());
    
}