

void Button::redraw(RenderTarget* dest){
    if(state == UX_DISABLED)return;
    Sprite sp = sprtbuff[state];
    sp.setPosition(x,y);
    dest->draw(sp);

}



void Button::setImage(Sprite tx){
    imbf = Sprite(tx);
    image=true;
}

void Button::pre_render(){

    rt.create(w*3, h);
    text.render();
    if(image){
        auto bounds = imbf.getTextureRect();
        imbf.scale((double)w/bounds.width, (double)h/bounds.height);
        imbf.setPosition(0,0);
        imbf.setColor(colors[UX::CI_FILL]);
        rt.draw(imbf);
        text.draw_to(&rt,this, Vector2i(0,0));

        imbf.setPosition(w,0);
        imbf.setColor(colors[UX::CI_MOVERFILL]);
        rt.draw(imbf);
        text.draw_to(&rt,this, Vector2i(w,0));

        imbf.setPosition(w+w,0);
        imbf.setColor(colors[UX::CI_MDOWN_FILL]);
        rt.draw(imbf);
        text.draw_to(&rt,this, Vector2i(w+w,0));


    }else{
        RectangleShape sh(Vector2f(w,h));
        RectangleShape brdr(Vector2f(w-borderWidth*2,h-borderWidth*2));
        brdr.setFillColor(_UX_TRANSPARENT);
        brdr.setOutlineThickness(borderWidth);
        brdr.setPosition(borderWidth,borderWidth);

        sh.setFillColor(colors[CI_FILL]);
        brdr.setOutlineColor(colors[CI_BORDER]);
        rt.draw(sh);
        rt.draw(brdr);
        text.draw_to(&rt,this, Vector2i(0,0));
        brdr.move(w,0);

        sh.setPosition(w,0);
        sh.setFillColor(colors[CI_MOVERFILL]);
        brdr.setOutlineColor(colors[CI_MOVERBORDER]);
        rt.draw(sh);
        rt.draw(brdr);

        text.draw_to(&rt,this, Vector2i(w,0));
        brdr.move(w,0);


        sh.setPosition(w+w,0);
        sh.setFillColor(colors[CI_MDOWN_FILL]);
        brdr.setOutlineColor(colors[CI_MDOWN_BORDER]);
        rt.draw(sh);
        rt.draw(brdr);
        text.draw_to(&rt,this, Vector2i(w+w,0));

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
    
    int mx, my;
    context->accessMouseCoords(&mx,&my);
    bool md = false;
    bool mu = false;


    if(contains(mx,my)){
        if(anims[state] != nullptr)anims[state]->ensureCompletion(this);
        state=UX_HOVER;
        md = context->mouseDowns[Mouse::Left];
        mu = context->mouseUps[Mouse::Left];
        if(md){
            state = UX_ACTIVE;
        }
        if (mu){
            state = UX_ACTIVE;
            context->events.enqueue(event);
            

        }
    }else{
        state=UX_NORMAL;
    }
    

}

void Button::setTextNode(TextNode t){

    text=t;

}
