#include "Main/Application.h"
#include "Module/ModuleRender.h"
#include "Module/ModuleTexture.h"
#include "ModuleScore.h"

ModuleScore::ModuleScore(bool active) : Module(active)
{
	
}

bool ModuleScore::Init()
{
	unitRect = {
		static_cast<int>(SCREEN_WIDTH * 0.93F), 0, static_cast<int>(SCREEN_WIDTH * 0.07F), static_cast<int>(SCREEN_HEIGHT * 0.05F)
	};
	tenRect = {
		static_cast<int>(SCREEN_WIDTH * 0.86F), 0, static_cast<int>(SCREEN_WIDTH * 0.07F), static_cast<int>(SCREEN_HEIGHT * 0.05F)
	};
	centRect = {
		static_cast<int>(SCREEN_WIDTH * 0.79F), 0, static_cast<int>(SCREEN_WIDTH * 0.07F), static_cast<int>(SCREEN_HEIGHT * 0.05F)
	};
	numberTextures.push_back(App->texture->Load("Assets/Textures/0.png"));
	numberTextures.push_back(App->texture->Load("Assets/Textures/1.png"));
	numberTextures.push_back(App->texture->Load("Assets/Textures/2.png"));
	numberTextures.push_back(App->texture->Load("Assets/Textures/3.png"));
	numberTextures.push_back(App->texture->Load("Assets/Textures/4.png"));
	numberTextures.push_back(App->texture->Load("Assets/Textures/5.png"));
	numberTextures.push_back(App->texture->Load("Assets/Textures/6.png"));
	numberTextures.push_back(App->texture->Load("Assets/Textures/7.png"));
	numberTextures.push_back(App->texture->Load("Assets/Textures/8.png"));
	numberTextures.push_back(App->texture->Load("Assets/Textures/9.png"));

	unitText = numberTextures[0];
	tenText = numberTextures[0];
	centText = numberTextures[0];

	return true;
}

UpdateStatus ModuleScore::Update()
{
	App->renderer->Blit(unitText, &unitRect);
	App->renderer->Blit(tenText, &tenRect);
	App->renderer->Blit(centText, &centRect);
	return UpdateStatus::CONTINUE;
}

bool ModuleScore::CleanUp()
{
	for (auto iterator = numberTextures.begin(); iterator != numberTextures.end(); ++iterator)
	{
		App->texture->Unload(*iterator);
	}
	numberTextures.clear();
	value = 0;
	return true;
}

void ModuleScore::IncreseValue()
{
	++value;
	int number = value;
	unitText = numberTextures[number % 10];
	number = number / 10;
	tenText = numberTextures[number % 10];
	number = number / 10;
	centText = numberTextures[number % 10];
}