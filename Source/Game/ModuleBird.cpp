#include "Main/Application.h"
#include "Module/ModuleAudio.h"
#include "Module/ModuleInput.h"
#include "Module/ModuleRender.h"
#include "Module/ModuleTexture.h"
#include "ModuleBird.h"
#include "ModulePlayScene.h"

#include "SDL.h"

ModuleBird::ModuleBird(bool active) : Module(active)
{
	
}

bool ModuleBird::Init()
{
	birdRect =
	{
		10, 150, SCREEN_WIDTH * 0.07F, SCREEN_HEIGHT * 0.05F
	};
	birdText = App->texture->Load("Assets/Textures/birdanimation.png");

	birdAnimation.frames.push_back({ 0, 0, 34, 24 });
	birdAnimation.frames.push_back({ 34, 0, 34, 24 });
	birdAnimation.frames.push_back({ 68, 0, 34, 24 });

	birdAnimation.speed = 0.03F;

	return true;
}

UpdateStatus ModuleBird::Update()
{
	
	if (birdRect.y + birdRect.h >= SCREEN_HEIGHT * 0.80F)
	{
		App->audio->PlayFx(App->playScene->dieSFX);
		App->playScene->enableNextFrame = true;
	}
	else
	{
		birdRect.y += 1.5F;
	}

	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KeyState::DOWN
		|| App->input->GetMouseButton(SDL_BUTTON_LEFT) == KeyState::DOWN)
	{
		birdRect.y -= 57.0F;
	}
	App->renderer->Blit(birdText, &birdRect, &birdAnimation.GetCurrentFrame());
	return UpdateStatus::CONTINUE;
}

bool ModuleBird::CleanUp()
{
	App->texture->Unload(birdText);
	return true;
}