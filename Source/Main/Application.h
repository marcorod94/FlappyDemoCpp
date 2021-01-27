#ifndef Application_h
#define Application_h

#include <vector>

class Module;
class ModuleAudio;
class ModuleBird;
class ModuleGameOverScene;
class ModuleInput;
class ModuleMenuScene;
class ModulePlayScene;
class ModuleRender;
class ModuleScore;
class ModuleTexture;
class ModuleTube;
class ModuleWindow;
enum class UpdateStatus;

class Application {
public:
	ModuleInput* input = nullptr;
	ModuleWindow* window = nullptr;
	ModuleRender* renderer = nullptr;
	ModuleTexture* texture = nullptr;
	ModuleAudio* audio = nullptr;

	ModuleMenuScene* menuScene = nullptr;
	ModulePlayScene* playScene = nullptr;
	ModuleGameOverScene* gameOverScene = nullptr;
	ModuleTube* tubes = nullptr;
	ModuleBird* bird = nullptr;
	ModuleScore* score = nullptr;

	Application();
	~Application();

	bool Init() const;
	UpdateStatus Update() const;
	bool CleanUp() const;

private:
	std::vector<Module*> modules;
};
extern Application* App;
#endif