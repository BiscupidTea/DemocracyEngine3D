#include "EarthGame.h"


EarthGame::EarthGame()
{
}

EarthGame::~EarthGame()
{
}

void EarthGame::Init()
{
	PlayerPosition = vec3{ 0, 0, -50 };
	PlayerScale = vec3{ 100, 100, 100 };
	PlayerRotation = vec3{ 0, 0, 0 };
	PlayerColor = vec4{ 1, 1, 1, 1 };

	timer = new DemoTimer();

	const char* path = "rsc/demoDie.png";
	player = new Sprite(path, 100, 200, PlayerColor, PlayerPosition, PlayerScale, PlayerRotation);

	path = "rsc/democracy.png";
	floor = new Sprite(path, 200, 200, vec4{ 1, 1, 1, 1 }, vec3{ 0, -50, -50 }, vec3{ 1000, 1000, 1000 }, vec3{ -90, 0, 0 });

	anim = new Animation();
	anim->AddFrame(0, 0, 639, 588, 26838, 588, 4, 42);
	player->AddAnimation(anim);

	playerSpeed = 5;
	cameraRotation = -1;
}

void EarthGame::Update()
{
	if (input->IsKeyPressed(GLFW_KEY_S))
	{
		vec3 dir(0, 0, -playerSpeed);
		TranslateCamera(dir);
	}
	if (input->IsKeyPressed(GLFW_KEY_W))
	{
		vec3 dir(0, 0, playerSpeed);
		TranslateCamera(dir);
	}
	if (input->IsKeyPressed(GLFW_KEY_A))
	{
		vec3 dir(-playerSpeed, 0, 0);
		TranslateCamera(dir);
	}
	if (input->IsKeyPressed(GLFW_KEY_D))
	{
		vec3 dir(playerSpeed, 0, 0);
		TranslateCamera(dir);
	}
	if (input->IsKeyPressed(GLFW_KEY_X))
	{
		cameraRotation += 0.1;
		RotateCamera(vec3{0,0,0});
	}

	player->Update(timer);
	floor->Draw();
	player->Draw();
}

void EarthGame::DeInit()
{
	delete player;
}
