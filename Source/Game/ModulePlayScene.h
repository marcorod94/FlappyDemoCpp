#ifndef ModulePlayScene_H
#define ModulePlayScene_H

#include "Module/Module.h"

struct SDL_FRect;
struct SDL_Texture;
struct Mix_Chunk;

class ModulePlayScene : public Module
{
public:
	SDL_Texture* backgroundText = nullptr;
	SDL_Texture* groundText = nullptr;

	SDL_FRect backgroundRect;
	SDL_FRect groundRect;

	Mix_Chunk* dieSFX;
	Mix_Chunk* hitSFX;
	Mix_Chunk* pointSFX;

	explicit ModulePlayScene(bool active = true);
	~ModulePlayScene() override = default;
	bool Init() override;
	UpdateStatus PreUpdate() override;
	UpdateStatus Update() override;
	UpdateStatus PostUpdate() override;
	bool CleanUp() override;
};
#endif
