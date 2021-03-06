
#ifndef __MODULESCENEINTRO_H__
#define __MODULESCENEINTRO_H__

#include "Module.h"
#include "Globals.h"
#include "Animation.h"
#include"Path.h"


struct SDL_Texture;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(bool startEnabled);

	~ModuleSceneIntro();


	bool Start() override;
	update_status Update() override;

	update_status PostUpdate() override;

	bool CleanUp() override;

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	Animation fAnim;
	Animation* menuAnim = nullptr;
	
};

#endif