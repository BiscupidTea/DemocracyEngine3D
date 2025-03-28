#include "BaseGame.h"

#include "../Entities/Triangle.h"
#include "../Entities/Square.h"
#include "../Tools/DemoTimer.h"

using namespace DemoEngine_Window;
using namespace DemoEngine_Renderer;
using namespace DemoEngine_Animations;

namespace DemoEngine_BaseGame
{
	BaseGame::BaseGame()
	{
		vec2 windowXY;
		windowXY.x = 1024;
		windowXY.y = 720;

		window = new Window(windowXY.x, windowXY.y, "Democracy Engine");
		renderer = new Renderer(windowXY);
		input = new Input(window);

		Init();
	}

	BaseGame::~BaseGame()
	{
		delete renderer;
		delete window;
		delete input;
	}

	void BaseGame::EngineLoop()
	{

		while (!window->ShouldClose())
		{
			DemoTimer::Update(glfwGetTime());
			renderer->Update();

			Update();

			window->Update();
		}
		DeInit();
	}

	void BaseGame::SetMainCameraPosition(vec3 NewPosition)
	{
		renderer->SetCameraPosition(NewPosition);
	}

	void BaseGame::TranslateCamera(vec3 dir)
	{
		renderer->TranslateCamera(dir);
	}

	void BaseGame::RotateCamera(vec3 newRotation)
	{
		renderer->RotateCamera(newRotation);
	}

	void BaseGame::Init()
	{

	}

	void BaseGame::Update()
	{

	}

	void BaseGame::DeInit()
	{

	}
}
