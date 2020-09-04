

typedef int Tile;
#define TILESPERCHUNK 32
#define MAXWORLDMAG 10000




struct Chunk{

    Tile contents[TILESPERCHUNK][TILESPERCHUNK];
    RenderTexture buffer;

    void render(){
        for (int i = 0 ; i < TILESPERCHUNK; i ++){

            for(int j = 0; j < TILESPERCHUNK; j++){

                

            }

        }



    }


};



class World{

    private:
        unordered_map<string, Chunk> chunks;
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

                    nc.contents[i][j] = noise.noise(i+left,j+left,0);

                }

            }
            


        }








    public:
        World(int seed){

            noise = PerlinNoise(seed);
            this->seed=seed;


            getChunk(-32,-32);

        }


        void draw(RenderWindow *window){



        }




};