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

	anim = new Animation();
	anim->AddFrame(0, 0, 639, 588, 26838, 588, 4, 42);
	player->AddAnimation(anim);

	playerSpeed = 5;
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
		player->rotateY(5);
	}

	player->Update(timer);
	player->Draw();
}

void EarthGame::DeInit()
{
	delete player;
}
