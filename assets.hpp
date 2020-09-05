


class TextureLoader{
public:
    Texture buffer;
    int cx = -ASSET_DIM;

    TextureLoader(string path, size_t count){
        loadFolderToBuffer(path,count);
    }

    void loadFolderToBuffer(string path, size_t count){
        glob_t glob_result;
        glob(path.c_str(),GLOB_TILDE,NULL,&glob_result);
        RenderTexture overall;
        overall.create(count*500,ASSET_DIM);
        for(int i = 0 ; i < glob_result.gl_pathc; i++){
            
            Texture temp;

            string cf = glob_result.gl_pathv[i];
            if(cf.substr(cf.length()-4) != "png"){
                continue;
            }
            temp.loadFromFile(cf);
            
            
            Sprite tsp(temp);
            tsp.setPosition(i*ASSET_DIM,0);
            overall.draw(tsp);

        }

        Texture text(overall.getTexture());
        buffer = text;
    
    }


    Sprite popSprite(){
        cx+=ASSET_DIM;
        return Sprite(buffer,IntRect(cx,0,ASSET_DIM,ASSET_DIM));

    }





};










Sprite tileSprite;


namespace Tiles{

    #define TILECOUNT 10

    Sprite sp_grass;
    Sprite sp_sand;

    Sprite* tile_sprites[TILECOUNT] = {&sp_grass, &sp_sand};
    


    void loadTiles(){
        TextureLoader *txl_tiles = new TextureLoader("Assets/World/Tiles/*", TILECOUNT);
        sp_grass = txl_tiles->popSprite();
        sp_sand = txl_tiles->popSprite();
    }

    Sprite get(Tile t){
        return *(tile_sprites[t]); 
    }
    
    






};






void loadAllAssets(){


    Tiles::loadTiles();

}