#ifndef _MODULESHOP_H_
#define _MODULESHOP_H_

#include "Module.h"
#include "Animation.h"
#include"Path.h"

struct SDL_Texture;

class ModuleShop : public Module
{
public:
	//Constructor
	ModuleShop(bool startEnabled);

	//Destructor
	~ModuleShop();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update() override;
	bool CleanUp();

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;
	void select();

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* selectorTexture = nullptr;
	int tienda[6][2];
	int tiendaX = 0, tiendaY = 0;
	enum weapon { Cluster, Phoenix, Falcon, Bullpup, S_Shell, T_Laser, Bomb, Napalm, Gunpod, Ceiling, MegaCrush, Exit };
	int wpos = 0;
};
#endif // !_MODULESHOP_H_