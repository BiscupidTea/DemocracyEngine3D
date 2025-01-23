#include "EarthGame.h"


EarthGame::EarthGame()
{
}

EarthGame::~EarthGame()
{
}

void EarthGame::Init()
{
    Sposition = vec3{1024 / 2, 720 / 2, 0};
    Sscale = vec3{400, 400, 1};
    Srotation = vec3{0, 0, 0};
    Scolor = vec4{1, 1, 1, 1};

    timer = new DemoEngine_Animations::DemoTimer();

    image = new DemoEngine_Entities::Sprite("rsc/democracy.png", 1024, 730, Scolor, Sposition, Sscale, Srotation);

    const char* tileMapFiles[] = {
        "rsc/PruebaTereno_Terreno.csv",
        "rsc/PruebaTereno_Obstaculos.csv"
    };

    tileMap = new DemoEngine_TileMap::TileMap(
        vec3(200,600, 0), vec3(0, 0, 0), vec3(50, 50, 1),
        "rsc/Tiles.tsx", {tileMapFiles[0], tileMapFiles[1]}, "rsc/tilemap_packed.png");
}

void EarthGame::Update()
{
    if (input->IsKeyPressed(GLFW_KEY_S))
    {
        image->Translate(vec3(0, -1, 0));
    }
    else if (input->IsKeyPressed(GLFW_KEY_W))
    {
        image->Translate(vec3(0, 1, 0));
    }
    else if (input->IsKeyPressed(GLFW_KEY_A))
    {
        image->Translate(vec3(-1, 0, 0));
    }
    else if (input->IsKeyPressed(GLFW_KEY_D))
    {
        image->Translate(vec3(1, 0, 0));
    }

    tileMap->Draw();
}

void EarthGame::DeInit()
{
    delete image;
    delete tileMap;
}
