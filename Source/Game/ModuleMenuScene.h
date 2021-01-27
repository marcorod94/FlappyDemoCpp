#ifndef ModuleMenuScene_H
#define ModuleMenuScene_H

#include "Module/Module.h"

struct SDL_FRect;
struct SDL_Texture;

class ModuleMenuScene : public Module
{
public:
	SDL_Texture* backgroundText = nullptr;
	SDL_Texture* playBtnText = nullptr;

	SDL_FRect backgroundRect;
	SDL_FRect playBtnRect;

	explicit ModuleMenuScene(bool active = true);
	~ModuleMenuScene() override = default;
	bool Init() override;
	UpdateStatus Update() override;
	UpdateStatus PostUpdate() override;
	bool CleanUp() override;

};
#endif
