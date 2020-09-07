
void Label::pre_render(){
    contents.render();
}

void Label::redraw(RenderTarget* dest){

    //contents.draw_to(dest,this,Vector2i(x,y));
    contents.buffer.setPosition(x,y);
    dest->draw(contents.buffer);

}
void Label::logic(){

}