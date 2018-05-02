void level9(SDL_Renderer* renderer, vector<Block>& blockVec, EndZoneWall& end, Player& p){
    SDL_Rect wall1 = {0,0,10,720};
    SDL_Rect wall2 = {1270,0,10,720};
    SDL_Rect wall3 = {10,0,1260,10};
    SDL_Rect wall4 = {10,710,1260,10};
    Block leftwall(0,0,10,720,renderer, wall1, true);
    Block rightwall(1270,0,10,720,renderer, wall2, true);
    Block topwall(10,0,1260,10,renderer, wall3, true);
    Block bottomwall(10,710,1260,10,renderer, wall4, true);
	SDL_Rect grayTop1 = {10,10,140,30};
    SDL_Rect grayTop2 = {290,10,140,30};
    SDL_Rect grayTop3 = {570,10,140,30};
    SDL_Rect grayTop4 = {850,10,420,30};

    SDL_Rect grayBot1 = {10,680,140,30};
    SDL_Rect grayBot2 = {290,680,140,30};
    SDL_Rect grayBot3 = {570,680,140,30};
    SDL_Rect grayBot4 = {850,680,140,30};
    SDL_Rect grayBot5 = {1130,680,140,30};

    SDL_Rect topWall1 = {140,10,140,350};
    SDL_Rect botWall1 = {140,360,140,350};
    SDL_Rect topWall2 = {430,10,140,200};
    SDL_Rect botWall2 = {430,310,140,400};
    SDL_Rect topWall3 = {710,10,140,400};
    SDL_Rect botWall3 = {710,450,140,260};
    SDL_Rect botWall4 = {1130,150,140,560};

	Block g1(10,10,140,30,renderer, grayTop1, false);
    Block g2(290,10,140,30,renderer, grayTop2, false);
    Block g3(570,10,140,30,renderer, grayTop2, false);
    Block g4(850,10,420,30,renderer, grayTop4, false);
    Block g5(10,680,140,30,renderer, grayBot1, false);
    Block g6(290,680,140,30,renderer, grayBot2, false);
    Block g7(570,680,140,30,renderer, grayBot3, false);
    Block g8(850,680,140,30,renderer, grayBot4, false);
    Block g9(1130,680,140,30,renderer, grayBot5, false);

    Block b1(140,10,140,350,renderer, topWall1, true);
    Block b2(140,360,140,350,renderer, botWall1, true);
    Block b3(430,10,140,200,renderer, topWall2, true);
    Block b4(430,310,140,400,renderer, botWall2, true);
    Block b5(710,10,140,400,renderer, topWall3, true);
    Block b6(710,450,140,260,renderer, botWall3, true);
    Block b7(1130,150,140,560,renderer, botWall4, true);

	blockVec.push_back(leftwall);
    blockVec.push_back(rightwall);
    blockVec.push_back(topwall);
    blockVec.push_back(bottomwall);
    blockVec.push_back(g1);
    blockVec.push_back(g2);
    blockVec.push_back(g3);
    blockVec.push_back(g4);
    blockVec.push_back(g5);
    blockVec.push_back(g6);
    blockVec.push_back(g7);
    blockVec.push_back(g8);
    blockVec.push_back(g9);
    blockVec.push_back(b1);
    blockVec.push_back(b2);
    blockVec.push_back(b3);
    blockVec.push_back(b4);
    blockVec.push_back(b5);
    blockVec.push_back(b6);
    blockVec.push_back(b7);

    for(auto i : blockVec){
        i.draw();
    }

    end.setX(1170);
    end.setY(670);
    p.setX(75);
    p.setY(640);

    end.draw();
}