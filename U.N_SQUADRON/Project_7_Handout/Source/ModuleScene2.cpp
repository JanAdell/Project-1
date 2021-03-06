#include "ModuleScene2.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleHud.h"
#include "ModuleScene.h"
#include "ModuleInput.h"
#include "ModuleSceneWin.h"
#include "ModuleFonts.h"
#include "ModuleParticles.h"
#include "SDL/include/SDL_scancode.h"


ModuleScene2::ModuleScene2(bool startEnabled) : Module(startEnabled)
{

}

ModuleScene2::~ModuleScene2() {
	

}
// Load assets
bool ModuleScene2::Start()
{
	victory_counter = 0;
	App->hud->Enable();
	App->player->Enable();
	App->enemies->Enable();
	App->collisions->Enable();
	//App->particles->Enable();

	LOG("Loading background assets\n");

	bool ret = true;

	char lookupTable[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz  0123456789.,��?!*$%&()+-/:;<=>@�    " };	yellowFont = App->fonts->Load("Assets/FontY.png", lookupTable, 5);
	greenFont = App->fonts->Load("Assets/FontG.png", lookupTable, 5);

	bgTexture = App->textures->Load("Assets/background2.png");

	App->audio->PlayMusic("Assets/EnemyAirforce.ogg", 6);

	left_spawn_counter = 0;

	for (int i = 0; i < MAX_LEFT_SPAWNER; i++) left_spawn_positions[i] = 0;
	
	//Left spawn coords
	left_spawn_positions[WHITE_JET_1] = 1000;
	left_spawn_positions[WHITE_JET_2] = 1550;
	left_spawn_positions[WHITE_JET_3] = 2000;
	left_spawn_positions[WHITE_JET_4] = 3000;
	left_spawn_positions[WHITE_JET_5] = 3300;
	left_spawn_positions[WHITE_JET_6] = 3600;
	left_spawn_positions[PURPLE_JACKAL] = 4900;
	


	// Enemies ---	

	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 1500, 700);
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 1750, 200);

	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 1770, -70);

	//-------------------------------------------------------------

	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 2230, -70);

	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 2250, 200);
	//------------------------------------------------------------
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 2600, 200);
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 2850, 700);
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 3000, 200);
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 3250, 700);
	//-------------------------------------------------------------
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 3500, 700);
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 3700, 200);
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 3900, 700);
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 4100, 200);

	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 4150, -70);
	//-------------------------------------------------------------

	App->enemies->AddEnemy(ENEMY_TYPE::WHITE_JET_LVL_2, 4300, -70);

	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 4400, 700);
	
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 4450, -70);

	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 4500, 700);
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 4700, 700);
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 4800, 700);
	App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 5000, 700);
	
	//-----------BOSS----------------------------------------------
	App->enemies->AddEnemy(ENEMY_TYPE::BOSS_PURPLE_JACKAL, 5950, 600);
	App->enemies->AddEnemy(ENEMY_TYPE::BOSS_PURPLE_JACKAL, 5950, 400);
	App->enemies->AddEnemy(ENEMY_TYPE::BOSS_PURPLE_JACKAL, 6000, 450);


	//falten verticals

	//Test enemies
	//App->enemies->AddEnemy(ENEMY_TYPE::WHITE_JET_LVL_2, 1000, 400);
	//App->enemies->AddEnemy(ENEMY_TYPE::GREEN_JET_LVL_2, 1000, 600);
	

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	moveBG1 = 0;
	moveBG2 = 1;
	loopBG = -1;
	limitBG = 0;
	return ret;
}

update_status ModuleScene2::Update() 
{
	
	if (left_spawn_counter < MAX_LEFT_SPAWNER) {
		int camera_x = App->render->camera.x;
		if (camera_x >= left_spawn_positions[left_spawn_counter]) {
			switch (left_spawner(left_spawn_counter))
			{
			case WHITE_JET_1:
				App->enemies->AddEnemy(ENEMY_TYPE::WHITE_JET_LVL_2, camera_x, 200);
				break;
			case WHITE_JET_2:
				App->enemies->AddEnemy(ENEMY_TYPE::WHITE_JET_LVL_2, camera_x, 200);
				break;
			case WHITE_JET_3:
				App->enemies->AddEnemy(ENEMY_TYPE::WHITE_JET_LVL_2, camera_x, 200);
				break;
			case WHITE_JET_4:
				App->enemies->AddEnemy(ENEMY_TYPE::WHITE_JET_LVL_2, camera_x, 200);
				break;
			case WHITE_JET_5:
				App->enemies->AddEnemy(ENEMY_TYPE::WHITE_JET_LVL_2, camera_x, 700);
				break;
			case WHITE_JET_6:
				App->enemies->AddEnemy(ENEMY_TYPE::WHITE_JET_LVL_2, camera_x, 200);
				break;
			default:
				break;
			}
			left_spawn_counter++;
		}

	}

	/*if (App->render->camera.x >= 5000) {
		App->transition->FadeToBlack(this, (Module*)App->sceneWin);
	}*/

	if (App->player->destroyed == true) {
		App->transition->FadeToBlack(this, (Module*)App->loose);
		App->player->collider->pendingToDelete = true;
		App->particles->enemy_shot.isAlive = false;
		App->hud->Disable();
		//App->particles->CleanUp();
		App->collisions->CleanUp();
	}

	if (App->input->keys[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN) {
		App->transition->FadeToBlack(this, (Module*)App->initialScreen, 90);
	}

	if (App->input->keys[SDL_SCANCODE_F6] == KEY_STATE::KEY_DOWN) {
		App->transition->FadeToBlack(this, (Module*)App->sceneWin, 90);
	}

	if (App->input->keys[SDL_SCANCODE_F7] == KEY_STATE::KEY_DOWN) {
		App->transition->FadeToBlack(this, (Module*)App->loose, 90);
	}
	if (App->input->keys[SDL_SCANCODE_F8] == KEY_STATE::KEY_DOWN) {
		//App->audio->StopMusic();
		App->transition->FadeToBlack(this, (Module*)App->shop);
	}

	if (App->input->keys[SDL_SCANCODE_F10] == KEY_STATE::KEY_DOWN) {
		App->transition->FadeToBlack(this, (Module*)App->scene, 90);
	}

	if (App->input->keys[SDL_SCANCODE_F11] == KEY_STATE::KEY_DOWN) {
		App->transition->FadeToBlack(this, (Module*)App->scene2, 90);
	}

	if (victory_counter == 3) {
		App->transition->FadeToBlack(this, (Module*)App->sceneWin);
	}

	App->render->camera.x += SCREEN_SPEED;
	updateBackground();


	limitBG = App->render->camera.x + SCREEN_WIDTH;


	return update_status::UPDATE_CONTINUE;
}

void ModuleScene2::updateBackground() {



	if ((limitBG % (3859 / 2)) == 0) {
		loopBG += 1;
		if (loopBG > 1) {
			((loopBG % 2) == 0) ? moveBG1 += 2 : moveBG2 += 2;
		}
	}

	Y_BG = -(App->player->position.y * 0.32f) + -12 ;


}


// Update: draw background

update_status ModuleScene2::PostUpdate() {

	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 3859 * moveBG1, Y_BG, NULL, 2);
	App->render->Blit(bgTexture, 3859 * moveBG2, Y_BG, NULL, 2);

	App->fonts->BlitText(715, 10, greenFont, "2");


	return update_status::UPDATE_CONTINUE;
}

bool ModuleScene2::CleanUp()
{
	//Enable (and properly disable) the player module

	App->player->Disable();
	App->enemies->Disable();
	//App->particles->Disable();
	App->player->CleanUp();
	App->enemies->CleanUp();
	App->particles->CleanUp();
	App->hud->Disable();
	App->fonts->UnLoad(yellowFont);
	App->fonts->UnLoad(greenFont);

	App->audio->StopMusic();

	App->textures->Unload(bgTexture);


	return true;
}
