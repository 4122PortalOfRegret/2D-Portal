void level9(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p){
    SDL_Rect wall1 = {0,0,10,720};
    SDL_Rect wall2 = {1270,0,10,720};
    SDL_Rect wall3 = {10,0,1260,10};
    SDL_Rect wall4 = {10,710,1260,10};
    Block leftwall(0,0,10,720,renderer, wall1, true);
    Block rightwall(1270,0,10,720,renderer, wall2, true);
    Block topwall(10,0,1260,10,renderer, wall3, true);
    Block bottomwall(10,710,1260,10,renderer, wall4, true);

    SDL_Rect floor = {10,680,1260,30};
    
    SDL_Rect bot1 = {150,620,30,100};
    SDL_Rect bot2 = {250,580,30,40};
    SDL_Rect bot3 = {380,580,30,40};
    SDL_Rect bot4 = {410,550,30,70};
    SDL_Rect bot5 = {540,550,120,40};
  	SDL_Rect bot6 = {740,580,120,40};
  	SDL_Rect bot7 = {940,550,30,70};
  	SDL_Rect bot8 = {1050,550,30,40};
  	SDL_Rect bot9 = {1080,520,30,70};
  	SDL_Rect bot10 = {1110,490,30,100};
  	SDL_Rect bot11 = {1140,460,60,130};

  	SDL_Rect mid1 = {1020,400,60,30};
  	SDL_Rect mid2 = {960,430,90,30};
  	SDL_Rect mid3 = {830,430,30,30};
  	SDL_Rect mid4 = {700,430,30,30};
  	SDL_Rect mid5 = {600,410,30,50};
  	SDL_Rect mid6 = {470,410,30,50};
  	SDL_Rect mid7 = {370,430,100,30};
  	SDL_Rect mid8 = {300,410,30,50};
  	SDL_Rect mid9 = {270,380,30,30};
  	SDL_Rect mid10 = {240,350,30,30};
  	SDL_Rect mid11 = {150,320,90,30};

  	SDL_Rect top1 = {300,260,250,30};
  	SDL_Rect top2 = {650,260,250,30};
  	SDL_Rect top3 = {1000,260,270,30};

  	Block floorB(10,680,1260,30,renderer,mid1,true);

  	Block bot1B(150,620,30,100,renderer,bot1,true);
  	Block bot2B(250,580,30,40,renderer,bot2,true);
  	Block bot3B(380,580,30,40,renderer,bot3,true);
  	Block bot4B(410,550,30,70,renderer,bot4,true);
  	Block bot5B(540,550,120,40,renderer,bot5,true);
  	Block bot6B(740,580,120,40,renderer,bot6,true);
  	Block bot7B(940,550,30,70,renderer,bot7,true);
  	Block bot8B(1050,550,30,40,renderer,bot8,true);
  	Block bot9B(1080,520,30,70,renderer,bot9,true);
  	Block bot10B(1110,490,30,100,renderer,bot10,true);
  	Block bot11B(1140,460,60,130,renderer,bot11,true);

  	Block mid1B(1020,400,60,30,renderer,mid1,true);
  	Block mid2B(960,430,90,30,renderer,mid2,true);
  	Block mid3B(830,430,30,30,renderer,mid3,true);
  	Block mid4B(700,430,30,30,renderer,mid4,true);
  	Block mid5B(600,410,30,50,renderer,mid5,true);
  	Block mid6B(470,410,30,50,renderer,mid6,true);
  	Block mid7B(370,430,100,30,renderer,mid7,true);
  	Block mid8B(300,410,30,50,renderer,mid8,true);
  	Block mid9B(270,380,30,30,renderer,mid9,true);
  	Block mid10B(240,350,30,30,renderer,mid10,true);
  	Block mid11B(150,320,90,30,renderer,mid11,true);

  	Block top1B(300,260,250,30,renderer,top1,true);
  	Block top2B(650,260,250,30,renderer,top2,true);
  	Block top3B(1000,260,270,30,renderer,top3,true);

	blockVec.push_back(leftwall);
    blockVec.push_back(rightwall);
    blockVec.push_back(topwall);
    blockVec.push_back(bottomwall);

    blockVec.push_back(floorB);

    blockVec.push_back(bot1B);
    blockVec.push_back(bot2B);
    blockVec.push_back(bot3B);
    blockVec.push_back(bot4B);
    blockVec.push_back(bot5B);
    blockVec.push_back(bot6B);
    blockVec.push_back(bot7B);
    blockVec.push_back(bot8B);
    blockVec.push_back(bot9B);
    blockVec.push_back(bot10B);
    blockVec.push_back(bot11B);

    blockVec.push_back(mid1B);
    blockVec.push_back(mid2B);
    blockVec.push_back(mid3B);
    blockVec.push_back(mid4B);
    blockVec.push_back(mid5B);
    blockVec.push_back(mid6B);
    blockVec.push_back(mid7B);
    blockVec.push_back(mid8B);
    blockVec.push_back(mid9B);
    blockVec.push_back(mid10B);
    blockVec.push_back(mid11B);

    blockVec.push_back(top1B);
    blockVec.push_back(top2B);
    blockVec.push_back(top3B);

    for(auto i : blockVec){
        i.draw();
    }

    end.setX(1170);
    end.setY(200);
    p.setX(75);
    p.setY(600);

    end.draw();
}