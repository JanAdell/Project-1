#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/sprites/praticles/particles_rz.png");
	//texture = App->textures->Load("Assets/sprites/particles/particles.png");
	
	//Hit particles
	//Blackbird
	blackbird.anim.PushBack({ 1325,1746,556,316 });
	blackbird.lifetime = 2;

	//Purple Jackal
	jackal.anim.PushBack({ 1507,2125,160,100 });
	jackal.lifetime = 2;

	//Green Fighter
	fighter.anim.PushBack({ 1353,1518,428,156 });
	fighter.lifetime = 2;

	//Hit particle
	player_hit.anim.PushBack({192,186,288,84});
	player_hit.anim.PushBack({ 492,186,282,90 });
	player_hit.anim.PushBack({ 786,186,282,84 });
	player_hit.anim.PushBack({ 1080,186,282,84 });
	player_hit.anim.loop = false;
	player_hit.anim.speed = 0.5f;

	// Explosion particle
	explosion.anim.PushBack({246, 0, 144, 150 });
	explosion.anim.PushBack({402, 0, 174, 156 });
	explosion.anim.PushBack({588,0,174,162});
	explosion.anim.PushBack({780,0,186,174});
	explosion.anim.PushBack({978,0,192,174});
	explosion.anim.PushBack({1182,0,186,168});
	explosion.anim.PushBack({0,180,180,162});
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;
	
	//Player shot
	laser.anim.PushBack({ 9 * 2, 183 * 2, 27 * 2, 18 * 2 });
	laser.anim.PushBack({ 87 * 2, 180 * 2, 24 * 2, 18 * 2 });
	laser.anim.PushBack({ 168 * 2, 183 * 2, 27 * 2, 15 * 2 });
	laser.anim.PushBack({ 237 * 2, 183 * 2, 18 * 2, 12 * 2 });
	laser.anim.PushBack({ 297 * 2, 183 * 2, 27 * 2, 9 * 2 });
	laser.anim.PushBack({ 363 * 2, 183 * 2, 24 * 2, 12 * 2 });
	laser.anim.PushBack({ 426 * 2, 180 * 2, 24 * 2, 15 * 2 });
	laser.anim.PushBack({ 483 * 2, 180 * 2, 24 * 2, 18 * 2 });
	//laser.collider->dmg = 5;
	laser.speed.x = 20;
	laser.lifetime = 180;
	laser.anim.speed = 0.3f;

	// Enemy Shot particle
	enemy_shot.anim.PushBack({ 63, 34, 21, 15 });
	enemy_shot.anim.PushBack({ 93,31, 18, 21 });
	enemy_shot.anim.PushBack({ 120, 34, 15, 15 });
	enemy_shot.anim.PushBack({ 147,31, 15, 21 });
	enemy_shot.anim.speed = 0.3f;
	enemy_shot.lifetime = 200;
	
	//Green Fighter Claw
	g_claw.anim.PushBack({0,1152,89,47});
	g_claw.anim.PushBack({ 107,1119,87,110 });
	g_claw.anim.speed = 0.3f;
	g_claw.anim.loop = false;
	g_claw.speed.y = -3;

	g_claw_o.anim.PushBack({ 195,1111,158,124 });
	g_claw_o.anim.PushBack({ 364,1113,148,122 });
	g_claw_o.anim.speed = 0.3f;
	g_claw_o.anim.loop = false;
	g_claw_o.speed.x = -5;

	//White Jet Missile
	w_missile_down.anim.PushBack({1086,2129,44,44});
	w_missile_down.anim.PushBack({ 1094,2217,52,52 });
	w_missile_down.anim.speed = 0.3;
	

	w_missile_up.anim.PushBack({ 613,2399,44,44 });
	w_missile_up.anim.PushBack({ 621,2303,52,52 });
	w_missile_up.anim.speed = 0.3;
	

	w_missile_down_l.anim.PushBack({ 1143,2305,44,44 });
	w_missile_down_l.anim.PushBack({ 1127,2393,52,52 });
	w_missile_down_l.anim.speed = 0.3;
	

	w_missile_up_l.anim.PushBack({ 665,2225,44,44 });
	w_missile_up_l.anim.PushBack({ 649,2129,52,52 });
	w_missile_up_l.anim.speed = 0.3;
	

	//-----Special Weapon Particles---
	//Tri Laser particles
	t_laser1.anim.PushBack({1,1601,153,115});
	t_laser1.anim.PushBack({ 270,1446,438,212 });
	t_laser1.anim.PushBack({ 819,1423,468,240 });
		
	t_laser2.anim.PushBack({ 10,1720,143,66 });
	t_laser2.anim.PushBack({ 270,1726,460,89 });
	t_laser2.anim.PushBack({ 801,1715,494,104 });
	
	t_laser3.anim.PushBack({ 28,1814,126,98 });
	t_laser3.anim.PushBack({ 276,1867,386,182 });
	t_laser3.anim.PushBack({ 789,1863,506,240 });
	
	t_laser1.speed.x = 15;
	t_laser1.speed.y = -13;
	t_laser1.lifetime = 180;
	t_laser1.anim.speed = 0.5f;
	t_laser1.anim.loop = false;

	t_laser2.speed.x = 20;
	t_laser2.lifetime = 180;
	t_laser2.anim.speed = 0.5f;
	t_laser2.anim.loop = false;

	t_laser3.speed.x = 15;
	t_laser3.speed.y = 13;
	t_laser3.lifetime = 180;
	t_laser3.anim.speed = 0.5f;
	t_laser3.anim.loop = false;

	//Straight Laser Particles
	s_laser.anim.PushBack({ 0,1288,130,104 });
	s_laser.anim.PushBack({ 711,1287,289,105 });
	s_laser.anim.PushBack({ 1038,1286,320,94 });
	s_laser.anim.PushBack({ 1384,1278,396,96 });
	s_laser.anim.speed = 0.5f;
	s_laser.anim.loop = false;
	s_laser.speed.x = 20;
	s_laser.lifetime = 200;

	//Bomb Particles - downward missiles
	dw_missile.anim.PushBack({ 39,2161,80,84 });
	dw_missile.anim.PushBack({ 123,2165,92,72 });
	dw_missile.anim.speed = 0.5f;
	dw_missile.anim.loop = false;
	dw_missile.lifetime = 500;
	dw_missile.speed.y = 15;

	//Gunpod
	g_p_turret.anim.PushBack({28,2057,92,44});
	g_p_turret.anim.PushBack({128,2057,116,44});
	g_p_turret.speed.x = 1;
	g_p_turret.anim.speed = 0.2;
	   
	g_p_bullets.anim.PushBack({268,2057,60,68});
	g_p_bullets.speed.x = 10;
	g_p_bullets.speed.y = -10;


	//-----Boss 1 Particles----------
	//Round Bomb
	round_bomb.anim.PushBack({ 1248, 672, 36, 40 });
	round_bomb.anim.PushBack({ 1300,672, 36, 40 });
	round_bomb.anim.PushBack({ 1248, 672, 36, 40 });
	round_bomb.anim.PushBack({ 1300,672, 36, 40 });
	round_bomb.anim.PushBack({ 1248, 672, 36, 40 });
	round_bomb.anim.PushBack({ 1300,672, 36, 40 });
	round_bomb.anim.PushBack({ 1248, 672, 36, 40 });
	round_bomb.anim.PushBack({ 1300,672, 36, 40 });
	round_bomb.anim.PushBack({ 1352, 668, 44, 48 });
	round_bomb.anim.PushBack({ 1352, 668, 44, 48 });
	round_bomb.anim.PushBack({ 1248,732, 60, 64 });
	round_bomb.anim.PushBack({ 1248,732, 60, 64 });
	round_bomb.anim.PushBack({ 1320,748, 36, 36 });
	round_bomb.anim.PushBack({ 1372, 736, 56, 56 });
	round_bomb.anim.PushBack({ 1444, 732, 60, 60 });
	round_bomb.anim.PushBack({ 1444, 732, 60, 60 });
	round_bomb.speed.x = -6;
	round_bomb.speed.y = -6;
	round_bomb.anim.loop = false;
	round_bomb.anim.speed = 0.25f;

	//Scatter explosion after
	subshot1.anim.PushBack({1328,812,16,40});
	subshot1.anim.PushBack({1512,808,16,48});
	subshot1.speed.y = -7;

	subshot4.anim.PushBack({ 1328,936,16,40 });
	subshot4.anim.PushBack({ 1512,932,16,48 });
	subshot4.speed.y = 7;

	subshot2.anim.PushBack({ 1248,892,40,16 });
	subshot2.anim.PushBack({ 1428,892,48,16 });
	subshot2.speed.x = -7;

	subshot3.anim.PushBack({ 1372,892,40,16 });
	subshot3.anim.PushBack({ 1552,892,48,16 });
	subshot3.speed.x = 7;

	subshot5.anim.PushBack({ 1268,832,24,32 });
	subshot5.anim.PushBack({ 1452,832,28,32 });
	subshot5.speed.y = -6;
	subshot5.speed.x = -6;

	subshot6.anim.PushBack({ 1368,832,24,32 });
	subshot6.anim.PushBack({ 1548,832,28,32 });
	subshot6.speed.y = -6;
	subshot6.speed.x =  6;

	subshot7.anim.PushBack({ 1368,924,24,32 });
	subshot7.anim.PushBack({ 1548,924,28,32 });
	subshot7.speed.y = 6;
	subshot7.speed.x = 6;

	subshot8.anim.PushBack({ 1268,924,24,32 });
	subshot8.anim.PushBack({ 1452,924,28,32 });
	subshot8.speed.y =  6;
	subshot8.speed.x = -6;

	//Back bullets
	backshot.anim.PushBack({1592,1096,60,48});
	backshot.anim.PushBack({ 1672,1096,65,48 });
	backshot.speed.x = -5;
	backshot.anim.speed = 0.2f;

	//Bomb drops
	dropbomb.anim.PushBack({1248,1012,96,40});
	dropbomb.anim.PushBack({ 1248,1068,96,76 });
	dropbomb.speed.x = -5;
	dropbomb.speed.y = 4;
	dropbomb.anim.loop = false;
	dropbomb.lifetime = 1000;
	dropbomb.anim.speed = 0.1f;

	//-----Boss 2 Particles----------
	//Backbomb
	b_bomb.anim.PushBack({ 56,981,51,50 });
	b_bomb.anim.PushBack({ 56,981,51,50 });
	b_bomb.anim.PushBack({ 56,981,51,50 });
	b_bomb.anim.PushBack({ 56,981,51,50 });
	b_bomb.anim.PushBack({ 114,983,36,40 });
	b_bomb.anim.PushBack({ 169,966,72,74 });
	b_bomb.anim.PushBack({ 266,959,80,89 });
	b_bomb.anim.PushBack({ 363,965,83,79});
	b_bomb.anim.PushBack({ 488,949,74,82 });
	b_bomb.speed.x = -10;
	b_bomb.anim.loop = false;
	b_bomb.anim.speed = 0.3f;

	//Missile
	f_missile.anim.PushBack({45,807,69,63});
	f_missile.anim.PushBack({ 45,807,69,63 });
	f_missile.anim.PushBack({ 45,807,69,63 });
	f_missile.anim.PushBack({156,776,126,125});
	f_missile.anim.PushBack({314,723,217,194});
	f_missile.anim.PushBack({536,707,207,198});
	f_missile.anim.PushBack({748,743,209,219});
	f_missile.anim.PushBack({957,967,204,209});
	f_missile.anim.speed = 0.3f;
	f_missile.speed.x = 10;
	f_missile.anim.loop = false;
	
	return true;
}

bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}
	//App->textures->Unload();
	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			delete particles[i];
			particles[i] = nullptr;
			break;
		}
	}
}

update_status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			delete particle;
			particles[i] = nullptr;
			
		}
	}
	g_p_turret.position.x = App->player->position.x + 130;
	g_p_turret.position.y = App->player->position.y;

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->Blit(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return update_status::UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, ColliderType colliderType, uint delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			Particle* p = new Particle(particle);

			p->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			p->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			p->position.y = y;

			//Adding the particle's collider
			if (colliderType != ColliderType::NONE)
				p->collider = App->collisions->AddCollider(p->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = p;
			break;
		}
	}
}