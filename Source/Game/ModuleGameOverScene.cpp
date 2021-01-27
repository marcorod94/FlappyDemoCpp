#include "Main/Application.h"
#include "Module/ModuleInput.h"
#include "Module/ModuleRender.h"
#include "Module/ModuleTexture.h"
#include "ModuleGameOverScene.h"
#include "ModuleMenuScene.h"

#include "SDL.h"

ModuleGameOverScene::ModuleGameOverScene(bool active) : Module(active)
{
	backgroundRect =
	{
		0, 0, SCREEN_WIDTH, SCREEN_HEIGHT
	};

	gameOverRect = {
		0, 0, static_cast<int>(SCREEN_WIDTH * 0.5F), static_cast<int>(SCREEN_HEIGHT * 0.15F)
	};
	gameOverRect.x = static_cast<int>(SCREEN_WIDTH * 0.5F - gameOverRect.w * 0.5F);
	gameOverRect.y = static_cast<int>(SCREEN_HEIGHT * 0.5F - gameOverRect.h * 0.5F);
}

bool ModuleGameOverScene::Init()
{
	backgroundText = App->texture->Load("Assets/Textures/bg.png");
	gameOverText = App->texture->Load("Assets/Textures/gameover.png");
	return true;
}

UpdateStatus ModuleGameOverScene::Update()
{
	App->renderer->Blit(backgroundText, &backgroundRect);
	App->renderer->Blit(gameOverText, &gameOverRect);
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KeyState::DOWN
		|| App->input->GetMouseButton(SDL_BUTTON_LEFT) == KeyState::DOWN)
	{
		enableNextFrame = true;
	}
	return UpdateStatus::CONTINUE;
}

UpdateStatus ModuleGameOverScene::PostUpdate()
{
	if (enableNextFrame)
	{
		Disable();
		App->menuScene->Enable();
		enableNextFrame = false;
	}
	return UpdateStatus::CONTINUE;
}

bool ModuleGameOverScene::CleanUp()
{
	App->texture->Unload(backgroundText);
	App->texture->Unload(gameOverText);
	return true;
}