#include "EarthGame.h"


EarthGame::EarthGame()
{
}

EarthGame::~EarthGame()
{
}

void EarthGame::Init()
{
    PlayerPosition = vec3{0, 0, -50};
    PlayerScale = vec3{100, 100, 100};
    PlayerRotation = vec3{0, 0, 0};
    PlayerColor = vec4{1, 1, 1, 1};

    timer = new DemoTimer();

    const char* path = "rsc/SpritesAnimations/Orange.png";
    floor = new Cube(vec3{0, -100, 0}, vec3{0, 0, 0}, vec3{1000, 5, 1000}, path);
    floor->setColor(vec4{255, 255, 255, 255});
    floor->setMaterial(YellowRubber);

    cube = new Cube(vec3{100, 0, 0}, vec3{0, 0, 0}, vec3{100, 100, 100}, path);
    cube->setColor(vec4{255, 255, 255, 255});
    cube->setMaterial(Emerald);

    light = new Cube(vec3{0, 250, 0}, vec3{0, 0, 0}, vec3{50, 50, 50});
    light->setColor(vec4{255, 255, 255, 255});
    light->setMaterial(Pearl);

    player = new Cube(vec3{0, 10, 200}, vec3{0, 0, 0}, vec3{50, 50, 50});
    player->setColor(vec4{0, 255, 0, 255});

    playerSpeed = 5;
}

void EarthGame::Update()
{
    if (input->IsKeyPressed(GLFW_KEY_UP))cube->Translate(vec3{0, 0, -playerSpeed});
    if (input->IsKeyPressed(GLFW_KEY_DOWN))cube->Translate(vec3{0, 0, playerSpeed});
    if (input->IsKeyPressed(GLFW_KEY_LEFT))cube->Translate(vec3{-playerSpeed, 0, 0});
    if (input->IsKeyPressed(GLFW_KEY_RIGHT))cube->Translate(vec3{playerSpeed, 0, 0});
    if (input->IsKeyPressed(GLFW_KEY_0))cube->Translate(vec3{0, playerSpeed, 0});
    if (input->IsKeyPressed(GLFW_KEY_9))cube->Translate(vec3{0, -playerSpeed, 0});

    floor->Draw();
    cube->Draw();
    light->Draw();
    //player->Draw();
}

void EarthGame::DeInit()
{
    delete cube;
    delete light;

    delete player;
    delete floor;
    delete timer;
}
