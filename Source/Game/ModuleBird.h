#ifndef ModuleBird_H
#define ModuleBird_H

#include "Module/Module.h"
#include "Utils/Animation.h"

struct SDL_FRect;
struct SDL_Texture;

class ModuleBird : public Module
{
public:
	SDL_Texture* birdText = nullptr;

	Animation birdAnimation;

	SDL_FRect birdRect;

	ModuleBird(bool active = true);
	~ModuleBird() override = default;
	bool Init() override;
	UpdateStatus Update() override;
	bool CleanUp() override;
};
#endif
