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
    floor = new Cube(vec3{0, -100, 0}, vec3{0, 0, 0}, vec3{8000, 5, 8000}, path);
    floor->setColor(vec4{255, 255, 255, 255});
    floor->setMaterial(YellowRubber);

    cube = new Cube(vec3{0, 0, 0}, vec3{0, 0, 0}, vec3{100, 100, 100}, path);
    cube->setColor(vec4{255, 255, 255, 255});
    cube->setMaterial(Emerald);

    player = new Cube(vec3{0, 10, 200}, vec3{0, 0, 0}, vec3{50, 50, 50});
    player->setColor(vec4{0, 255, 0, 255});

    playerSpeed = 5;

    //lightManager->directionalLights.push_back({ glm::vec3(-0.3f, -1.0f, -0.3f), glm::vec3(1.0f) });
    lightManager->pointLights.push_back({ glm::vec3(-1000.0f, 500.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f) });
    lightManager->pointLights.push_back({ glm::vec3(1000.0f, 500.0f, 0.0f), glm::vec3(0.0f, 0.0f, 5.0f) });
    
    lightManager->spotLights.push_back({
        MainCamera->getPosition(),
        MainCamera->GetCameraFoward(),
        glm::vec3(1.0f),
        12.5f,
        17.5f
    });
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
    //player->Draw();
}

void EarthGame::DeInit()
{
    delete cube;

    delete player;
    delete floor;
    delete timer;
}
