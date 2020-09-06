

void Button::redraw(RenderTarget* dest){
    if(state == UX_DISABLED)return;
    Sprite sp = sprtbuff[state];
    sp.setPosition(x,y);
    dest->draw(sp);
}



void Button::setImage(Sprite tx){
    imbf = tx;
    image=true;
}

void Button::pre_render(){

    rt.create(w*3, h);
    if(image){
                
        rt.draw(imbf);
        imbf.setPosition(w,0);
        imbf.setColor(colors[UX::CI_MOVERFILL]);
        rt.draw(imbf);
        imbf.setPosition(w+w,0);
        imbf.setColor(colors[UX::CI_MDOWN_FILL]);
        rt.draw(imbf);

    }else{
        RectangleShape sh(Vector2f(w,h));
        sh.setFillColor(colors[CI_FILL]);
        sh.setOutlineColor(colors[CI_BORDER]);
        rt.draw(sh);
        sh.setPosition(w,0);
        sh.setFillColor(colors[CI_MOVERFILL]);
        sh.setOutlineColor(colors[CI_MOVERBORDER]);
        rt.draw(sh);
        sh.setPosition(w+w,0);
        sh.setFillColor(colors[CI_MDOWN_FILL]);
        sh.setOutlineColor(colors[CI_MDOWN_BORDER]);
        rt.draw(sh);
    }
    rt.display();
    //buffer.swap((Texture&)rt.getTexture());
    
    sprtbuff[0] = Sprite(rt.getTexture());
    sprtbuff[1] = Sprite(rt.getTexture());
    sprtbuff[2] = Sprite(rt.getTexture());
    sprtbuff[0].setTextureRect(TRISTATE_BUFF_1);
    sprtbuff[1].setTextureRect(TRISTATE_BUFF_2);
    sprtbuff[2].setTextureRect(TRISTATE_BUFF_3);
    
}


void Button::logic(){

    int mx=context->mouseMove.x;
    int my=context->mouseMove.y;
    if(!contains(mx,my)){
        state = UX_NORMAL;
        return;
    }
    bool mdown = context->mouseDown[Mouse::Left] && context->mouseStateChange;
    if(context->mouseStateChange && context->mouseRel[Mouse::Left]){
        context->events.enqueue(this->event);
    }
    if(mdown){
        state = UX_ACTIVE;
        
    }else{
        state = UX_HOVER;
    }
}