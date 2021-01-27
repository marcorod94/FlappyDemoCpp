#include "Application.h"
#include "Game/ModuleBird.h"
#include "Game/ModuleGameOverScene.h"
#include "Game/ModuleMenuScene.h"
#include "Game/ModulePlayScene.h"
#include "Game/ModuleScore.h"
#include "Game/ModuleTube.h"
#include "Main/Globals.h"
#include "Module/Module.h"
#include "Module/ModuleAudio.h"
#include "Module/ModuleInput.h"
#include "Module/ModuleRender.h"
#include "Module/ModuleTexture.h"
#include "Module/ModuleWindow.h"

Application::Application()
{
	modules.push_back(input = new ModuleInput());
	modules.push_back(texture = new ModuleTexture());
	modules.push_back(window = new ModuleWindow());
	modules.push_back(renderer = new ModuleRender());
	modules.push_back(audio = new ModuleAudio());

	// Game
	modules.push_back(menuScene = new ModuleMenuScene());
	modules.push_back(gameOverScene = new ModuleGameOverScene(false));
	modules.push_back(playScene = new ModulePlayScene(false));
	modules.push_back(tubes = new ModuleTube(false));
	modules.push_back(bird = new ModuleBird(false));
	modules.push_back(score = new ModuleScore(false));
}

Application::~Application()
{
	for (auto iterator = modules.begin(); iterator != modules.end(); ++iterator)
	{
		delete* iterator;
	}
}

bool Application::Init() const
{
	bool value = true;
	for (auto iterator = modules.begin(); iterator != modules.end(); ++iterator)
	{
		if ((*iterator)->IsEnabled())
		{
			value = (*iterator)->Init();
		}
	}
	return value;
}

UpdateStatus Application::Update() const {
	UpdateStatus value = UpdateStatus::CONTINUE;
	for (auto iterator = modules.begin(); iterator != modules.end()
		&& value == UpdateStatus::CONTINUE; ++iterator)
	{
		if ((*iterator)->IsEnabled())
		{
			value = (*iterator)->PreUpdate();
		}
	}
	for (auto iterator = modules.begin(); iterator != modules.end()
		&& value == UpdateStatus::CONTINUE; ++iterator)
	{
		if ((*iterator)->IsEnabled())
		{
			value = (*iterator)->Update();
		}
	}
	for (auto iterator = modules.begin(); iterator != modules.end()
		&& value == UpdateStatus::CONTINUE; ++iterator)
	{
		if ((*iterator)->IsEnabled())
		{
			value = (*iterator)->PostUpdate();
		}
	}
	return value;
}

bool Application::CleanUp() const {
	bool value = true;
	for (auto iterator = modules.begin(); iterator != modules.end(); ++iterator)
	{
		value = (*iterator)->CleanUp();
	}
	return value;
}