#ifndef ModuleTube_H
#define ModuleTube_H

#include "Module/Module.h"

struct SDL_FRect;
struct SDL_Texture;

constexpr int FLUCTUATION = 100;
constexpr int TUBE_GAP = 150;
constexpr int TUBE_WIDTH = 52;
constexpr int TUBE_HEIGHT = 320;
constexpr int TUBE_SPACING = 170;
constexpr int TUBE_COUNT = 4;

class Tube
{
public:
	SDL_Texture* topTubeText = nullptr;
	SDL_Texture* bottomTubeText = nullptr;

	SDL_FRect topTubeRect;
	SDL_FRect bottomTubeRect;
	SDL_FRect passTubeRect;

	bool passed = false;

	explicit Tube(float x);
	void Reposition(float x);
	bool IsColliding(const SDL_FRect* bird) const;
	float GetRandom() const;
	bool CleanUp();
};

class ModuleTube : public Module
{
public:

	std::vector<Tube*> tubes;

	explicit ModuleTube(bool active = true);
	~ModuleTube() override = default;
	bool Init() override;
	UpdateStatus Update() override;
	bool CleanUp() override;
};
#endif
