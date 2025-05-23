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
    
    const char* path = "rsc/SpritesAnimations/base.png";
    floor = new Sprite(path, 200, 200, vec4{1, 1, 1, 1}, vec3{0, -50, 0}, vec3{1000, 1000, 1000}, vec3{-90, 0, 0});

    path = "rsc/SpritesAnimations/Penguin_Walk_Back.png";
    pingu1 = new Sprite(path, 100, 100, 0, 0, 15, 100, vec4{1, 1, 1, 1}, vec3{0, -25, 0}, vec3{100, 100, 100},
                        vec3{0, 0, 0});
    pingu2 = new Sprite(path, 100, 100, 0, 0, 15, 100, vec4{1, 1, 1, 1}, vec3{0, -25, 100}, vec3{100, 100, 100},
                        vec3{0, 0, 0});

    path = "rsc/SpritesAnimations/base.png";
    cube = new Cube(vec3{0, 10, 0}, vec3{0, 0, 0}, vec3{100, 100, 100}, path);
    cube->setColor(vec4{255, 255, 255, 255});
    triangle = new Triangle(vec3{200, 10, 0}, vec3{0, 0, 0}, vec3{100, 100, 100});
    triangle->setColor(vec4{0, 255, 0, 255});
    square = new Square(vec3{-200, 10, 0}, vec3{0, 0, 0}, vec3{100, 100, 100});
    square->setColor(vec4{0, 0, 255, 255});

    player = new Cube(vec3{0, 10, 200}, vec3{0, 0, 0}, vec3{50, 50, 50});
    player->setColor(vec4{0, 255, 0, 255});

    playerSpeed = 5;
}

void EarthGame::Update()
{
    //cube->rotateX(1);
    //cube->rotateY(1);
    //cube->rotateZ(1);

    //triangle->rotateY(1);
    //square->rotateY(1);
    
    if (input->IsKeyPressed(GLFW_KEY_UP))cube->Translate(vec3{0,0,-playerSpeed});
    if (input->IsKeyPressed(GLFW_KEY_DOWN))cube->Translate(vec3{0,0,playerSpeed});
    if (input->IsKeyPressed(GLFW_KEY_LEFT))cube->Translate(vec3{-playerSpeed,0,0});
    if (input->IsKeyPressed(GLFW_KEY_RIGHT))cube->Translate(vec3{playerSpeed,0,0});
    if (input->IsKeyPressed(GLFW_KEY_0))cube->Translate(vec3{0,playerSpeed,0});
    if (input->IsKeyPressed(GLFW_KEY_9))cube->Translate(vec3{0,-playerSpeed,0});
    
    //floor->Draw();
    //triangle->Draw();
    //square->Draw();
    cube->Draw();
    //player->Draw();
}

void EarthGame::DeInit()
{
    delete cube;
    delete triangle;
    delete square;

    delete player;
    delete floor;
    delete pingu1;
    delete pingu2;
    delete timer;
}
