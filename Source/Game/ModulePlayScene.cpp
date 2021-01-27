#include "Main/Application.h"
#include "Module/ModuleAudio.h"
#include "Module/ModuleInput.h"
#include "Module/ModuleRender.h"
#include "Module/ModuleTexture.h"
#include "ModuleGameOverScene.h"
#include "ModuleBird.h"
#include "ModulePlayScene.h"
#include "ModuleScore.h"
#include "ModuleTube.h"

#include "SDL.h"

ModulePlayScene::ModulePlayScene(bool active) : Module(active)
{
	backgroundRect =
	{
		0, 0, SCREEN_WIDTH, SCREEN_HEIGHT
	};
	groundRect = {
		0, 0, SCREEN_WIDTH, static_cast<int>(SCREEN_HEIGHT * 0.15F)
	};
	groundRect.x = static_cast<int>(SCREEN_WIDTH * 0.5F - groundRect.w * 0.5F);
	groundRect.y = static_cast<int>(SCREEN_HEIGHT - groundRect.h);
}

bool ModulePlayScene::Init()
{
	backgroundText = App->texture->Load("Assets/Textures/bg.png");
	groundText = App->texture->Load("Assets/Textures/ground.png");

	dieSFX = App->audio->LoadFx("Assets/Audio/die.wav");
	hitSFX = App->audio->LoadFx("Assets/Audio/hit.wav");
	pointSFX = App->audio->LoadFx("Assets/Audio/point.wav");

	App->audio->PlayMusic("Assets/Audio/music.mp3");

	App->bird->Init();
	App->tubes->Init();
	App->score->Init();
	return true;
}

UpdateStatus ModulePlayScene::PreUpdate()
{
	if (enableNextFrame)
	{
		Disable();
		App->gameOverScene->Enable();
		enableNextFrame = false;
	}
	return UpdateStatus::CONTINUE;
}

UpdateStatus ModulePlayScene::Update()
{
	App->renderer->Blit(backgroundText, &backgroundRect);

	App->bird->Update();
	App->tubes->Update();
	App->score->Update();

	App->renderer->Blit(groundText, &groundRect);
	
	return UpdateStatus::CONTINUE;
}

UpdateStatus ModulePlayScene::PostUpdate()
{
	/*if (enableNextFrame)
	{
		Disable();
		App->gameOverScene->Enable();
		enableNextFrame = false;
	}*/
	return UpdateStatus::CONTINUE;
}

bool ModulePlayScene::CleanUp()
{
	App->texture->Unload(backgroundText);
	App->tubes->CleanUp();
	App->bird->CleanUp();
	App->score->CleanUp();
	return true;
}
