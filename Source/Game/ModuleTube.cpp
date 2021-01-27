#include "Utils/Collision.h"
#include "Main/Application.h"
#include "Module/ModuleAudio.h"
#include "Module/ModuleRender.h"
#include "Module/ModuleTexture.h"
#include "ModuleBird.h"
#include "ModulePlayScene.h"
#include "ModuleScore.h"
#include "ModuleTube.h"

Tube::Tube(float x)
{
	topTubeText = App->texture->Load("Assets/Textures/toptube.png");
	bottomTubeText = App->texture->Load("Assets/Textures/bottomtube.png");

	topTubeRect =
	{
		x, -GetRandom(), TUBE_WIDTH, TUBE_HEIGHT
	};

	bottomTubeRect =
	{
		x, topTubeRect.y + TUBE_GAP + TUBE_HEIGHT, TUBE_WIDTH, TUBE_HEIGHT
	};

	passTubeRect =
	{
		x, bottomTubeRect.y - TUBE_GAP, TUBE_WIDTH, TUBE_GAP
	};
}

void Tube::Reposition(float x)
{
	topTubeRect.x = x;
	topTubeRect.y = -GetRandom();
	bottomTubeRect.x = x;
	bottomTubeRect.y = topTubeRect.y + TUBE_GAP + TUBE_HEIGHT;
	passTubeRect.y = bottomTubeRect.y - TUBE_GAP;
	passed = false;
}

bool Tube::IsColliding(const SDL_FRect* bird) const
{
	return Collision::IsOverLaping(&topTubeRect, bird) ||
		Collision::IsOverLaping(&bottomTubeRect, bird);
}

float Tube::GetRandom() const
{
	return std::rand() % FLUCTUATION;
}

bool Tube::CleanUp()
{
	App->texture->Unload(topTubeText);
	App->texture->Unload(bottomTubeText);
	passed = false;
	return true;
}

ModuleTube::ModuleTube(bool active) : Module(active)
{

}

bool ModuleTube::Init()
{
	for (int i = 1; i <= TUBE_COUNT; i++)
	{
		tubes.push_back(new Tube(i * (TUBE_SPACING + TUBE_WIDTH)));
	}
	return true;
}

UpdateStatus ModuleTube::Update()
{
	for (auto tube : tubes)
	{
		tube->topTubeRect.x -= 1.5F;
		tube->bottomTubeRect.x -= 1.5F;
		App->renderer->Blit(tube->topTubeText, &tube->topTubeRect);
		App->renderer->Blit(tube->bottomTubeText, &tube->bottomTubeRect);
		if (tube->topTubeRect.x + TUBE_WIDTH < App->renderer->camera.x)
		{
			tube->Reposition(tube->topTubeRect.x + ((TUBE_WIDTH + TUBE_SPACING) * TUBE_COUNT));
		}
		if (tube->IsColliding(&App->bird->birdRect))
		{
			App->audio->PlayFx(App->playScene->hitSFX);
			App->audio->PlayFx(App->playScene->dieSFX);
			App->playScene->enableNextFrame = true;
		}
		if (App->bird->birdRect.x >= tube->topTubeRect.x + TUBE_WIDTH && tube->passed == false)
		{
			App->score->IncreseValue();
			tube->passed = true;
			App->audio->PlayFx(App->playScene->pointSFX);
		}
	}

	return UpdateStatus::CONTINUE;
}

bool ModuleTube::CleanUp()
{
	for (auto iterator = tubes.begin(); iterator != tubes.end(); iterator++)
	{
		(*iterator)->CleanUp();
	}
	tubes.clear();

	return true;
}
