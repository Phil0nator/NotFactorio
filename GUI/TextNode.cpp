TextNode::TextNode(Font f, string t){
    content=t;
    font=f;
}
TextNode::TextNode(TextNode other, string newtext){
    font=other.font;
    content=newtext;
    size=other.size;
    colors[0]= other.colors[0];
    colors[1]=other.colors[1];
    outlineThickness = other.outlineThickness;
    styles=other.styles;
    ta=other.ta;
}


void TextNode::render(){
    buffer.setFont(font);
    buffer.setString(content);
    buffer.setCharacterSize(size);
    buffer.setFillColor(colors[CI_FILL]);
    buffer.setOutlineColor(colors[CI_BORDER]);
    buffer.setOutlineThickness(outlineThickness);
    buffer.setStyle(styles);

}
#define _UX_TEXTNODE_DRAWBOTTOMPADDING size
#define _UX_TEXTNODE_DRAWTOLOC_CENTERX (translation.x+(dw/2) - (sw/2))
#define _UX_TEXTNODE_DRAWTOLOC_CENTERY (translation.y+(dh/2)-(sh/2))

#define _UX_TEXTNODE_DRAWTOLOC_LEFT translation.x
#define _UX_TEXTNODE_DRAWTOLOC_TOP translation.y

#define _UX_TEXTNODE_DRAWTOLOC_RIGHT (translation.x+dw-sw)
#define _UX_TEXTNODE_DRAWTOLOC_BOTTOM ((dh-sh)+translation.y-_UX_TEXTNODE_DRAWBOTTOMPADDING)


void TextNode::draw_to(RenderTarget* target, UXElement* source, Vector2i translation){
    int dw,dh;
    dw = source->w;
    dh = source->h;

    
    int sw, sh;
    auto dims = buffer.getLocalBounds();
    sw = dims.width;
    sh = dims.height;

    

    switch(ta){

        case Align::CENTER:
            buffer.setPosition(_UX_TEXTNODE_DRAWTOLOC_CENTERX,_UX_TEXTNODE_DRAWTOLOC_CENTERY);
            break;
        case Align::TOP|Align::LEFT:
            buffer.setPosition(_UX_TEXTNODE_DRAWTOLOC_LEFT,_UX_TEXTNODE_DRAWTOLOC_TOP);
            break;
        case Align::TOP|Align::RIGHT:
            buffer.setPosition(_UX_TEXTNODE_DRAWTOLOC_RIGHT,_UX_TEXTNODE_DRAWTOLOC_TOP);
            break;
        case Align::TOP:
            buffer.setPosition(_UX_TEXTNODE_DRAWTOLOC_CENTERX,_UX_TEXTNODE_DRAWTOLOC_TOP);
            break;
        case Align::BOTTOM|Align::LEFT:
            buffer.setPosition(_UX_TEXTNODE_DRAWTOLOC_LEFT,_UX_TEXTNODE_DRAWTOLOC_BOTTOM);
            break;
        case Align::BOTTOM|Align::RIGHT:
            buffer.setPosition(_UX_TEXTNODE_DRAWTOLOC_RIGHT,_UX_TEXTNODE_DRAWTOLOC_BOTTOM);
            break;
        case Align::BOTTOM:
            buffer.setPosition(_UX_TEXTNODE_DRAWTOLOC_CENTERX,_UX_TEXTNODE_DRAWTOLOC_BOTTOM);
            break;
        case Align::LEFT:
            buffer.setPosition(_UX_TEXTNODE_DRAWTOLOC_LEFT, _UX_TEXTNODE_DRAWTOLOC_CENTERY);
            break;
        case Align::RIGHT:
            buffer.setPosition(_UX_TEXTNODE_DRAWTOLOC_RIGHT, _UX_TEXTNODE_DRAWTOLOC_RIGHT);
            break;
        default:
            buffer.setPosition(_UX_TEXTNODE_DRAWTOLOC_CENTERX,_UX_TEXTNODE_DRAWTOLOC_CENTERY);
            break;
    }


    target->draw(buffer);

}


