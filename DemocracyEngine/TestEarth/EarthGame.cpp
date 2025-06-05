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

    const char* path = "rsc/Mesh/EnemyYukinko.fbx";

    yukinko = new Model3D(vec3{0, 0, 0}, vec3{0, 0, 0}, vec3{100, 100, 100}, path);
    //yukinko->setMaterial(Silver);
    
    path = "rsc/SpritesAnimations/Orange.png";

#pragma region Room
    floor = new Cube(vec3{0, -100, 0}, vec3{0, 0, 0}, vec3{4000, 5, 4000}, path);
    floor->setColor(vec4{1, 1, 1, 1});
    floor->setMaterial(YellowRubber);

    float halfSize = 2000.0f;
    float wallHeight = 500.0f;
    float wallThickness = 5.0f;

    wall1 = new Cube(vec3{-halfSize, wallHeight / 2 - 100, 0}, vec3{0, 90, 0}, vec3{4000, wallHeight, wallThickness}, path);
    wall1->setColor(vec4{1, 1, 1, 1});
    wall1->setMaterial(Obsidian);

    wall2 = new Cube(vec3{halfSize, wallHeight / 2 - 100, 0}, vec3{0, 90, 0}, vec3{4000, wallHeight, wallThickness}, path);
    wall2->setColor(vec4{1, 1, 1, 1});
    wall2->setMaterial(Brass);

    wall3 = new Cube(vec3{0, wallHeight / 2 - 100, -halfSize}, vec3{0, 0, 0}, vec3{4000, wallHeight, wallThickness}, path);
    wall3->setColor(vec4{1, 1, 1, 1});
    wall3->setMaterial(Copper);

    wall4 = new Cube(vec3{0, wallHeight / 2 - 100, halfSize}, vec3{0, 0, 0}, vec3{4000, wallHeight, wallThickness}, path);
    wall4->setColor(vec4{1, 1, 1, 1});
    wall4->setMaterial(WhitePlastic);

    Top = new Cube(vec3{0, wallHeight - 100, 0}, vec3{0, 0, 0}, vec3{4000, 5, 4000}, path);
    Top->setColor(vec4{1, 1, 1, 1});
    Top->setMaterial(Silver);
#pragma endregion

    cube = new Cube(vec3{0, 0, 0}, vec3{0, 0, 0}, vec3{100, 100, 100}, path);
    cube->setColor(vec4{1, 1, 1, 1});
    cube->setMaterial(Silver);

    player = new Cube(vec3{0, 10, 200}, vec3{0, 0, 0}, vec3{50, 50, 50});
    player->setColor(vec4{0, 1, 0, 1});

    playerSpeed = 5;
    
    float offset = halfSize * 0.75f;

    glm::vec3 corners[4] = {
        glm::vec3(-offset, 0, -offset),
        glm::vec3(offset, 0, -offset),
        glm::vec3(-offset, 0, offset),
        glm::vec3(offset, 0, offset)
    };

    glm::vec3 colors[4] = {
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 5.0f),
        glm::vec3(1.0f, 1.0f, 0.0f) 
    };

    for (int i = 0; i < 4; i++)
    {
        PointLight pl;
        pl.position = corners[i] + glm::vec3(0, 100, 0);
        pl.color = colors[i];
        pl.intensity = 500.0f;
        pl.constant = 5.0f;
        pl.linear = 0.07f;
        pl.quadratic = 0.002f;
        
        lightManager->pointLights.push_back(pl);
    }

    PointLight pl;
    pl.position = glm::vec3(0, 100, 0);
    pl.color = glm::vec3(0.0f, 0.0f, 5.0f);
    pl.intensity = 50.0f;
    pl.constant = 5.0f;
    pl.linear = 0.07f;
    pl.quadratic = 0.002f;
    lightManager->pointLights.push_back(pl);

    SpotLight spotLight;
    spotLight.position =  glm::vec3(0, 50, 2000);
    spotLight.direction = MainCamera->GetCameraFoward();
    spotLight.color = glm::vec3(1.0f);
    spotLight.cutOff = 20.0f;
    spotLight.outerCutOff = 30.0f;
    spotLight.constant = 1.0f;
    spotLight.linear = 0.007f;
    spotLight.quadratic = 0.0002f;
    spotLight.intensity = 900.0f;
    lightManager->spotLights.push_back(spotLight);
    
    lightManager->directionalLights.push_back({glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.3f)});
}

void EarthGame::Update()
{
    if (input->IsKeyPressed(GLFW_KEY_UP)) cube->Translate(vec3{0, 0, -playerSpeed});
    if (input->IsKeyPressed(GLFW_KEY_DOWN)) cube->Translate(vec3{0, 0, playerSpeed});
    if (input->IsKeyPressed(GLFW_KEY_LEFT)) cube->Translate(vec3{-playerSpeed, 0, 0});
    if (input->IsKeyPressed(GLFW_KEY_RIGHT)) cube->Translate(vec3{playerSpeed, 0, 0});
    if (input->IsKeyPressed(GLFW_KEY_0)) cube->Translate(vec3{0, playerSpeed, 0});
    if (input->IsKeyPressed(GLFW_KEY_9)) cube->Translate(vec3{0, -playerSpeed, 0});

    
    //if (input->IsKeyPressed(GLFW_KEY_UP))       lightManager->pointLights[4].position.z -= playerSpeed;
    //if (input->IsKeyPressed(GLFW_KEY_DOWN))     lightManager->pointLights[4].position.z += playerSpeed;
    //if (input->IsKeyPressed(GLFW_KEY_LEFT))     lightManager->pointLights[4].position.x -= playerSpeed;
    //if (input->IsKeyPressed(GLFW_KEY_RIGHT))    lightManager->pointLights[4].position.x += playerSpeed;
    //if (input->IsKeyPressed(GLFW_KEY_0))        lightManager->pointLights[4].position.y += playerSpeed;
    //if (input->IsKeyPressed(GLFW_KEY_9))        lightManager->pointLights[4].position.y -= playerSpeed;

    floor->Draw();
    wall1->Draw();
    wall2->Draw();
    wall3->Draw();
    wall4->Draw();
    //Top->Draw();

    cube->Draw();
    //player->Draw();

    yukinko->Draw();
}

void EarthGame::DeInit()
{
    delete cube;
    delete player;
    delete floor;
    delete wall1;
    delete wall2;
    delete wall3;
    delete wall4;
    delete Top;
    delete timer;
    delete yukinko;
}
