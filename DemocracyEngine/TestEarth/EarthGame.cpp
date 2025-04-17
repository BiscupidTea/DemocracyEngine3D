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

    const char* path = "rsc/demoDie.png";
    player = new Sprite(path, 100, 200, PlayerColor, PlayerPosition, PlayerScale, PlayerRotation);

    path = "rsc/democracy.png";
    floor = new Sprite(path, 200, 200, vec4{1, 1, 1, 1}, vec3{0, -50, 0}, vec3{1000, 1000, 1000}, vec3{-90, 0, 0});

    path = "rsc/Penguin_Walk_Back.png";
    pingu1 = new Sprite(path, 100, 100, 0, 0, 15, 100, vec4{1, 1, 1, 1}, vec3{0, -25, 0}, vec3{100, 100, 100},
                        vec3{0, 0, 0});
    pingu2 = new Sprite(path, 100, 100, 0, 0, 15, 100, vec4{1, 1, 1, 1}, vec3{0, -25, 100}, vec3{100, 100, 100},
                        vec3{0, 0, 0});

    cube = new Cube(vec3{0, 10, 0}, vec3{0, 0, 0}, vec3{100, 100, 100});
    cube->setColor(vec4{255, 0, 0, 255});
    triangle = new Triangle(vec3{200, 10, 0}, vec3{0, 0, 0}, vec3{100, 100, 100});
    triangle->setColor(vec4{0, 255, 0, 255});
    square = new Square(vec3{-200, 10, 0}, vec3{0, 0, 0}, vec3{100, 100, 100});
    square->setColor(vec4{0, 0, 255, 255});

    anim = new Animation();
    anim->AddFrame(0, 0, 639, 588, 26838, 588, 4, 42);
    player->AddAnimation(anim);

    playerSpeed = 5;
}

void EarthGame::Update()
{
    if (input->IsKeyPressed(GLFW_KEY_W))
    {
        GetMainCamera()->TranslateCamera(-GetMainCamera()->GetCameraFoward() * playerSpeed);
    }
    if (input->IsKeyPressed(GLFW_KEY_S))
    {
        GetMainCamera()->TranslateCamera(GetMainCamera()->GetCameraFoward() * playerSpeed);
    }
    if (input->IsKeyPressed(GLFW_KEY_A))
    {
        GetMainCamera()->TranslateCamera(-GetMainCamera()->GetCameraRight() * playerSpeed);
    }
    if (input->IsKeyPressed(GLFW_KEY_D))
    {
        GetMainCamera()->TranslateCamera(GetMainCamera()->GetCameraRight() * playerSpeed);
    }

    Camera* cam = GetMainCamera();
    vec3 currentRot = cam->GetRotation();

    if (input->IsKeyPressed(GLFW_KEY_RIGHT))
    {
        cam->RotateCamera(vec3(currentRot.x, currentRot.y + 1.0f, currentRot.z));
    }
    if (input->IsKeyPressed(GLFW_KEY_LEFT))
    {
        cam->RotateCamera(vec3(currentRot.x, currentRot.y - 1.0f, currentRot.z));
    }
    if (input->IsKeyPressed(GLFW_KEY_UP))
    {
        cam->RotateCamera(vec3(currentRot.x + 1.0f, currentRot.y, currentRot.z));
    }
    if (input->IsKeyPressed(GLFW_KEY_DOWN))
    {
        cam->RotateCamera(vec3(currentRot.x - 1.0f, currentRot.y, currentRot.z));
    }

    // cube->rotateX(1);
    // cube->rotateY(1);
    // cube->rotateZ(1);

    // triangle->rotateY(1);
    // square->rotateY(1);

    //player->Update(timer);
    //player->Draw();
    floor->Draw();
    //pingu1->Draw();
    //pingu2->Draw();
    triangle->Draw();
    square->Draw();
    cube->Draw();
}

void EarthGame::DeInit()
{
    delete player;
}
