#include "EarthGame.h"
#include "Scene/Scene.h"

EarthGame::EarthGame()
{
}

EarthGame::~EarthGame()
{
}

void EarthGame::Init()
{
    testScene = new Scene();

    PlayerPosition = vec3{0, 0, -50};
    PlayerScale = vec3{100, 100, 100};
    PlayerRotation = vec3{0, 0, 0};
    PlayerColor = vec4{1, 1, 1, 1};

    const char* path = "rsc/Mesh/Yukinko_Death.fbx";
    Model3D* yukinko = new Model3D(vec3{500, 0, 0}, vec3{0, 0, 0}, vec3{1, 1, 1}, path, false);

    path = "rsc/Mesh/Tank.fbx";
    this->Tank = new Model3D(vec3{0, 150, 0}, vec3{0, 0, 0}, vec3{40, 40, 40}, path, true);
    
    Tank->SetShowModelWireframe(true); 
    Tank->SetShowMeshesWireframe(true);

    path = "rsc/Mesh/muñecodeNieveGato_V2.fbx";
    this->SnowCat = new Model3D(vec3{0, 150, 500}, vec3{0, 0, 0}, vec3{1, 1, 1}, path, true);
    SnowCat->AddTexture("texture_baseColor", "rsc/Texturas/T_munecosDeNieve.png", false, true);
    yukinko->transform->SetParent(SnowCat->transform);

    Cube* cube = new Cube(vec3{0, 0, -1000}, vec3{0, 0, 0}, vec3{100, 100, 100}, path);
    cube->setMaterial(Silver);

    Cube* player = new Cube(vec3{0, 10, 200}, vec3{0, 0, 0}, vec3{50, 50, 50});
    
    playerSpeed = 5;

#pragma region Room
    path = "rsc/SpritesAnimations/White.png";
    Cube* floor = new Cube(vec3{0, -100, 0}, vec3{0, 0, 0}, vec3{4000, 5, 4000}, path);
    testScene->AddEntity(floor);
    testScene->AddPlane(Plane(vec3(0, 1, 0), floor->transform->GetGlobalPosition()));

    float halfSize = 2000.0f;
    float wallHeight = 500.0f;
    float wallThickness = 5.0f;

    Cube* wall1 = new Cube(vec3{-halfSize, wallHeight / 2 - 100, 0}, vec3{0, 90, 0}, vec3{4000, wallHeight, wallThickness}, path);
    wall1->setMaterial(Obsidian);
    testScene->AddEntity(wall1);
    testScene->AddPlane(Plane(vec3(1, 0, 0), vec3(-halfSize, 0, 0)));

    Cube* wall2 = new Cube(vec3{halfSize, wallHeight / 2 - 100, 0}, vec3{0, 90, 0}, vec3{4000, wallHeight, wallThickness}, path);
    wall2->setMaterial(Brass);
    testScene->AddEntity(wall2);
    testScene->AddPlane(Plane(vec3(-1, 0, 0), vec3(halfSize, 0, 0)));

    Cube* wall3 = new Cube(vec3{0, wallHeight / 2 - 100, -halfSize}, vec3{0, 0, 0}, vec3{4000, wallHeight, wallThickness}, path);
    wall3->setMaterial(Copper);
    testScene->AddEntity(wall3);
    testScene->AddPlane(Plane(vec3(0, 0, 1), vec3(0, 0, -halfSize)));

    Cube* wall4 = new Cube(vec3{0, wallHeight / 2 - 100, halfSize}, vec3{0, 0, 0}, vec3{4000, wallHeight, wallThickness}, path);
    wall4->setMaterial(WhitePlastic);
    testScene->AddEntity(wall4);
    testScene->AddPlane(Plane(vec3(0, 0, -1), vec3(0, 0, halfSize)));
    
#pragma endregion

#pragma region Lights
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
    spotLight.position = MainCamera->GetCameraPosition();
    spotLight.direction = MainCamera->GetCameraForward();
    spotLight.color = glm::vec3(1.0f);
    spotLight.cutOff = 20.0f;
    spotLight.outerCutOff = 30.0f;
    spotLight.constant = 1.0f;
    spotLight.linear = 0.007f;
    spotLight.quadratic = 0.0002f;
    spotLight.intensity = 900.0f;
    lightManager->spotLights.push_back(spotLight);

    lightManager->directionalLights.push_back({glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(1.0f)});
#pragma endregion

    tankTurretTransform = Tank->transform->FindChildByName("Turret");
    tankLeftCannonTransform = Tank->transform->FindChildByName("LeftCannon");
    tankRightCannonTransform = Tank->transform->FindChildByName("RightCannon");
    
    testScene->AddEntity(player);
    testScene->AddEntity(cube);
    testScene->AddEntity(yukinko);
    testScene->AddEntity(SnowCat);
    testScene->AddEntity(Tank);
}

void EarthGame::Update()
{
    MainCamera->SetCameraTarget(SnowCat->transform->GetGlobalPosition());

    if (input->IsKeyPressed(GLFW_KEY_UP)) Tank->transform->Translate(vec3{0, 0, -playerSpeed});
    if (input->IsKeyPressed(GLFW_KEY_DOWN)) Tank->transform->Translate(vec3{0, 0, playerSpeed});
    if (input->IsKeyPressed(GLFW_KEY_LEFT)) Tank->transform->Translate(vec3{-playerSpeed, 0, 0});
    if (input->IsKeyPressed(GLFW_KEY_RIGHT)) Tank->transform->Translate(vec3{playerSpeed, 0, 0});
    if (input->IsKeyPressed(GLFW_KEY_0)) Tank->transform->SetRotationY(Tank->transform->GetLocalRotation().y - playerSpeed);
    if (input->IsKeyPressed(GLFW_KEY_9)) Tank->transform->SetRotationY(Tank->transform->GetLocalRotation().y + playerSpeed);

    if (input->IsKeyPressed(GLFW_KEY_P)) tankTurretTransform->SetRotationY(tankTurretTransform->GetLocalRotation().y - playerSpeed);
    if (input->IsKeyPressed(GLFW_KEY_O)) tankTurretTransform->SetRotationY(tankTurretTransform->GetLocalRotation().y + playerSpeed);

    if (input->IsKeyPressed(GLFW_KEY_M))
    {
        tankRightCannonTransform->SetRotationX(tankRightCannonTransform->GetLocalRotation().x - playerSpeed);
        tankLeftCannonTransform->SetRotationX(tankLeftCannonTransform->GetLocalRotation().x - playerSpeed);
    }

    if (input->IsKeyPressed(GLFW_KEY_N))
    {
        tankRightCannonTransform->SetRotationX(tankRightCannonTransform->GetLocalRotation().x + playerSpeed);
        tankLeftCannonTransform->SetRotationX(tankLeftCannonTransform->GetLocalRotation().x + playerSpeed);
    }

    testScene->Draw(MainCamera);
    
    //Tank->DrawWireframes(vec4(0,1,0,1), vec4(1,0,1,1));
    
    std::cout << "Draw Calls: " << Renderer::GetRender()->GetDrawCalls() << std::endl;
}

void EarthGame::DeInit()
{
    delete testScene;
}
