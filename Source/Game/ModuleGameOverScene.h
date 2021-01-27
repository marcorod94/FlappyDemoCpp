#ifndef ModuleGameOverScene_H
#define ModuleGameOverScene_H

#include "Module/Module.h"

struct SDL_FRect;
struct SDL_Texture;

class ModuleGameOverScene : public Module
{
public:
	SDL_Texture* backgroundText = nullptr;
	SDL_Texture* gameOverText = nullptr;

	SDL_FRect backgroundRect;
	SDL_FRect gameOverRect;

	explicit ModuleGameOverScene(bool active = true);
	~ModuleGameOverScene() override = default;
	bool Init() override;
	UpdateStatus Update() override;
	UpdateStatus PostUpdate() override;
	bool CleanUp() override;
};
#endif
