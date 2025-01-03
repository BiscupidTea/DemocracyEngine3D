#include "EarthGame.h"


EarthGame::EarthGame()
{
}

EarthGame::~EarthGame()
{
}

void EarthGame::Init()
{
    Sposition = vec3{1024 /2, 720 / 2, 0};
    Sscale = vec3{400, 400, 1};
    Srotation = vec3{0, 0, 0};
    Scolor = vec4{1, 1, 1, 1};

    timer = new DemoEngine_Animations::DemoTimer();

    const char* path = "rsc/democracy.png";
    image = new DemoEngine_Entities::Sprite(path, 1024, 730, 1024/2, 0, 1024/2, 730/2, Scolor, Sposition, Sscale, Srotation);
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

    image->Draw();
}

void EarthGame::DeInit()
{
    delete image;
}
