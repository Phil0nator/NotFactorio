






struct Chunk{

    Tile contents[TILESPERCHUNK][TILESPERCHUNK];
    RenderTexture buffer;

    Chunk(){}

    Chunk(const Chunk& o){
        for (int i = 0 ; i < TILESPERCHUNK; i ++){

            for(int j = 0; j < TILESPERCHUNK; j++){

                contents[i][j] = o.contents[i][j];

            }

        }

        



    }

    void placetile(int x, int y, Tile tile){

        contents[x][y] = tile;
        Sprite s;
        s=Tiles::get(tile);
        s.setPosition(x*ASSET_DIM, y*ASSET_DIM);
        buffer.draw(s);
        

    }

    void render(){
        buffer.create(TILESPERCHUNK*ASSET_DIM, TILESPERCHUNK*ASSET_DIM);
        for (int i = 0 ; i < TILESPERCHUNK; i ++){

            for(int j = 0; j < TILESPERCHUNK; j++){
                Tile t = contents[i][j];
                if(t < 0.5){

                    placetile(i,j,GRASS);

                }else if (t > 0.5){

                    placetile(i,j,SAND);

                }

            }

        }



    }


};



class World{

    private:
        unordered_map<string, Chunk > chunks;
        int seed;
        PerlinNoise noise;
        
        RenderTexture buffer;
        Sprite drawer;

        int xoff = 0;
        int yoff = 0;


        Chunk *current_chunk = nullptr;

        bool chunkExists(int left, int top){

            return chunks.count(to_string(left)+":"+to_string(top)) == 1;


        }

        Chunk getChunk(int left, int top){

            if(chunkExists(left,top)){

                return chunks[to_string(left)+":"+to_string(top)];

            }

            generateChunk(left,top);
            return chunks[to_string(left)+":"+to_string(top)];

        }

        void generateChunk(int left, int top){
            
            if(chunkExists(left,top)){
                cout << "ERROR: regenerating existing chunk." << endl;
                return;
            }
            Chunk nc;
            for(int i = 0 ; i < TILESPERCHUNK; i++){

                for(int j = 0 ; j < TILESPERCHUNK; j++){
                    
                    //nc->contents[i][j] = noise.noise((double)(1/(i+left+0.01)),(double)(1/(j+top+0.01)),(double)0.1);
                    nc.contents[i][j] = (int)noise.noise((double)(i+left), (double)(j+top), (double)0);
                }

            }

            //chunks[to_string(left)+":"+to_string(top)] = nc;
            nc.render();
            chunks.insert({to_string(left)+":"+to_string(top), nc});

        }








    public:
        World(int seed){

            noise = PerlinNoise(seed);
            this->seed=seed;


            getChunk(-32,-32);

        }


        void draw(RenderWindow *window){

            Sprite drawer(Sprite(getChunk(xoff,yoff).buffer.getTexture()));
            

            window->draw(drawer);
        }




};