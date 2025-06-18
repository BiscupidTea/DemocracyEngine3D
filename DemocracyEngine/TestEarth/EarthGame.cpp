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

    const char* path = "rsc/Mesh/Yukinko_Death.fbx";
    yukinko = new Model3D(vec3{500, 0, 0}, vec3{0, 0, 0}, vec3{1, 1, 1}, path, false);

    path = "rsc/Mesh/backpack.obj";
    backPack = new Model3D(vec3{-500, 150, 0}, vec3{0, 0, 0}, vec3{40, 40, 40}, path, true);
    
    path = "rsc/Mesh/muñecodeNieveGato_V2.fbx";
    SnowCat = new Model3D(vec3{0, 150, 500}, vec3{0, 0, 0}, vec3{1, 1, 1}, path, true);
    SnowCat->AddTexture( "texture_baseColor", "rsc/Texturas/T_munecosDeNieve.png", false, true);
    

#pragma region Room
    path = "rsc/SpritesAnimations/White.png";
    floor = new Cube(vec3{0, -100, 0}, vec3{0, 0, 0}, vec3{4000, 5, 4000}, path);

    float halfSize = 2000.0f;
    float wallHeight = 500.0f;
    float wallThickness = 5.0f;
    
    path = "rsc/SpritesAnimations/Orange.png";

    wall1 = new Cube(vec3{-halfSize, wallHeight / 2 - 100, 0}, vec3{0, 90, 0}, vec3{4000, wallHeight, wallThickness}, path);
    wall1->setMaterial(Obsidian);

    wall2 = new Cube(vec3{halfSize, wallHeight / 2 - 100, 0}, vec3{0, 90, 0}, vec3{4000, wallHeight, wallThickness}, path);
    wall2->setMaterial(Brass);

    wall3 = new Cube(vec3{0, wallHeight / 2 - 100, -halfSize}, vec3{0, 0, 0}, vec3{4000, wallHeight, wallThickness}, path);
    wall3->setMaterial(Copper);

    wall4 = new Cube(vec3{0, wallHeight / 2 - 100, halfSize}, vec3{0, 0, 0}, vec3{4000, wallHeight, wallThickness}, path);
    wall4->setMaterial(WhitePlastic);

    Top = new Cube(vec3{0, wallHeight - 100, 0}, vec3{0, 0, 0}, vec3{4000, 5, 4000}, path);
    Top->setMaterial(Silver);
#pragma endregion

    cube = new Cube(vec3{0, 0, -1000}, vec3{0, 0, 0}, vec3{100, 100, 100}, path);
    cube->setMaterial(Silver);

    player = new Cube(vec3{0, 10, 200}, vec3{0, 0, 0}, vec3{50, 50, 50});

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
        pl.intensity = 100.0f;
        pl.constant = 1.0f;
        pl.linear = 0.012f;
        pl.quadratic = 0.007f;

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
    spotLight.position = glm::vec3(0, 50, 2000);
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
    MainCamera->SetCameraTarget(SnowCat->getPosition());

    if (input->IsKeyPressed(GLFW_KEY_UP)) SnowCat->Translate(vec3{0, 0, -playerSpeed});
    if (input->IsKeyPressed(GLFW_KEY_DOWN)) SnowCat->Translate(vec3{0, 0, playerSpeed});
    if (input->IsKeyPressed(GLFW_KEY_LEFT)) SnowCat->Translate(vec3{-playerSpeed, 0, 0});
    if (input->IsKeyPressed(GLFW_KEY_RIGHT)) SnowCat->Translate(vec3{playerSpeed, 0, 0});
    if (input->IsKeyPressed(GLFW_KEY_0)) SnowCat->Translate(vec3{0, playerSpeed, 0});
    if (input->IsKeyPressed(GLFW_KEY_9)) SnowCat->Translate(vec3{0, -playerSpeed, 0});
    if (input->IsKeyPressed(GLFW_KEY_P)) SnowCat->rotateY(playerSpeed);
    if (input->IsKeyPressed(GLFW_KEY_O)) SnowCat->rotateY(-playerSpeed);


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

    SnowCat->Draw();
    yukinko->Draw();
    backPack->Draw();
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
    delete backPack;
    delete SnowCat;
}
