#include "EarthGame.h"


EarthGame::EarthGame()
{
}

EarthGame::~EarthGame()
{
}

void EarthGame::Init()
{
    TileMapPosition = vec3{50, 500, 0};
    TileMapScale = vec3{50, 50, 0};
    TileMapRotation = vec3{0, 0, 0};
    TileMapColor = vec4{1, 1, 1, 1};

    PlayerPosition = vec3{300, 200, 0};
    PlayerScale = vec3{45, 45, 1};
    PlayerRotation = vec3{0, 0, 0};
    PlayerColor = vec4{1, 1, 1, 1};

    timer = new DemoTimer();

    const char* tileMapFiles[] = {
        "rsc/PruebaTereno_Terreno.csv",
        "rsc/PruebaTereno_Obstaculos.csv"
    };

    tileMap = new TileMap(
        TileMapPosition, TileMapRotation, TileMapScale,
        "rsc/TilesJunto.tsx", {tileMapFiles[0], tileMapFiles[1]}, "rsc/tilemap_packed.png");

    const char* path = "rsc/demoDie.png";
    player = new Sprite(path, 100, 200, PlayerColor, PlayerPosition, PlayerScale, PlayerRotation);
    lastPlayerPos = vec3(PlayerPosition.x, PlayerPosition.y, 0);

    anim = new Animation();
    anim->AddFrame(0, 0, 639, 588, 26838, 588, 4, 42);
    player->AddAnimation(anim);

    playerSpeed = 5;
}

void EarthGame::Update()
{
    if (input->IsKeyPressed(GLFW_KEY_S))
    {
        vec3 dir(0, -playerSpeed, 0);
        player->Translate(dir);
        MoveCameraPosition(dir);
    }
    if (input->IsKeyPressed(GLFW_KEY_W))
    {
        vec3 dir(0,playerSpeed, 0);
        player->Translate(dir);
        MoveCameraPosition(dir);
    }
    if (input->IsKeyPressed(GLFW_KEY_A))
    {
        vec3 dir(-playerSpeed, 0, 0);
        player->Translate(dir);
        MoveCameraPosition(dir);
    }
    if (input->IsKeyPressed(GLFW_KEY_D))
    {
        vec3 dir(playerSpeed, 0, 0);
        player->Translate(dir);
        MoveCameraPosition(dir);
    }

    if (tileMap->CheckCollision(*player))
    {
        player->setPosition(lastPlayerPos);
    }
    else
    {
        lastPlayerPos = player->getPosition();
    }
    
    tileMap->Draw();

    player->Update(timer);
    player->Draw();
}

void EarthGame::DeInit()
{
    delete player;
    delete tileMap;
}
