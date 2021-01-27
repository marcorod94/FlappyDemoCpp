#ifndef ModuleScore_H
#define ModuleScore_H

#include "Module/Module.h"

struct SDL_FRect;
struct SDL_Texture;

class ModuleScore : public Module
{
public:
	int value = 0;
	std::vector<SDL_Texture*> numberTextures;

	SDL_Texture* centText = nullptr;
	SDL_Texture* tenText = nullptr;
	SDL_Texture* unitText = nullptr;

	SDL_FRect centRect;
	SDL_FRect tenRect;
	SDL_FRect unitRect;

	ModuleScore(bool active = true);
	~ModuleScore() override = default;
	bool Init() override;
	UpdateStatus Update() override;
	bool CleanUp() override;

	void IncreseValue();
};
#endif
