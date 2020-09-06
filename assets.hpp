


class TextureLoader{
public:
    Texture buffer;
    int cx = -1;

    TextureLoader(string path, size_t count){
        loadFolderToBuffer(path,count);
    }

    void loadFolderToBuffer(string path, size_t count){
        glob_t glob_result;
        glob(path.c_str(),GLOB_TILDE,NULL,&glob_result);
        RenderTexture overall;
        overall.create(count*ASSET_DIM,ASSET_DIM);
        int loaded = 0;
        for(int i = 0 ; i < glob_result.gl_pathc; i++){
            
            Texture temp;

            string cf = glob_result.gl_pathv[i];
            
            bool success = temp.loadFromFile(cf);
            if(success){
                
                Sprite tsp(temp);
                tsp.setPosition(loaded*ASSET_DIM,0);
                tsp.setScale(ASSET_DIM/temp.getSize().x,ASSET_DIM/temp.getSize().y);
                loaded++;
                overall.draw(tsp);
            }
        }
        overall.display();
        Texture text(overall.getTexture());
        buffer = text;
        buffer.setRepeated(true);
    
    }


    Single constructNextSingle(){
        cx++;
        return Single(Sprite(buffer), IntRect(cx*ASSET_DIM,0,ASSET_DIM,ASSET_DIM));
    }





};










Sprite tileSprite;


namespace Tiles{

    #define TILECOUNT 10

    Texture buffer;
    Animation an_belt1("Assets/World/Tiles/belt1/beltsheet.png",22);
    Single s_blank;

    Asset* tile_sprites[TILECOUNT] = {&s_blank,&an_belt1};

    


    void loadTiles(){
        TextureLoader *txl_tiles = new TextureLoader("Assets/World/Tiles/*", TILECOUNT);
        s_blank = txl_tiles->constructNextSingle();
        buffer = txl_tiles->buffer;
    
    }

    Asset* get(Tile t){
        return (tile_sprites[t]); 
    }
    
    






};






void loadAllAssets(){


    Tiles::loadTiles();

}