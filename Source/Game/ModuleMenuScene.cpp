#include "Main/Application.h"
#include "Module/ModuleInput.h"
#include "Module/ModuleRender.h"
#include "Module/ModuleTexture.h"
#include "ModuleMenuScene.h"
#include "ModulePlayScene.h"

#include "SDL.h"

ModuleMenuScene::ModuleMenuScene(bool active): Module(active)
{
	backgroundRect =
	{
		0, 0, SCREEN_WIDTH, SCREEN_HEIGHT
	};

	playBtnRect = {
		0, 0, static_cast<int>(SCREEN_WIDTH * 0.75F), static_cast<int>(SCREEN_HEIGHT * 0.75F)
	};
	playBtnRect.x = static_cast<int>(SCREEN_WIDTH * 0.5F - playBtnRect.w * 0.5F);
	playBtnRect.y = static_cast<int>(SCREEN_HEIGHT * 0.5F - playBtnRect.h * 0.5F);
}

bool ModuleMenuScene::Init()
{	
	backgroundText = App->texture->Load("Assets/Textures/bg.png");
	playBtnText = App->texture->Load("Assets/Textures/message.png");
	return true;
}

UpdateStatus ModuleMenuScene::Update()
{
	App->renderer->Blit(backgroundText, &backgroundRect);
	App->renderer->Blit(playBtnText, &playBtnRect);
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KeyState::DOWN
		|| App->input->GetMouseButton(SDL_BUTTON_LEFT) == KeyState::DOWN)
	{
		enableNextFrame = true;
	}
	return UpdateStatus::CONTINUE;
}

UpdateStatus ModuleMenuScene::PostUpdate()
{
	if (enableNextFrame)
	{
		Disable();
		App->playScene->Enable();
		enableNextFrame = false;
	}
	return UpdateStatus::CONTINUE;
}


bool ModuleMenuScene::CleanUp()
{
	App->texture->Unload(backgroundText);
	App->texture->Unload(playBtnText);
	return true;
}