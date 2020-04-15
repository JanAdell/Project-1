#include "Enemy_BrownShip.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_BrownShip::Enemy_BrownShip(int x, int y) : Enemy(x, y)
{
	fly.PushBack({5,72,21,22});
	currentAnim = &fly;
	fly.speed = 0.01f;

	// TODO 3: Have the Brown Cookies describe a path in the screen
	path.PushBack({ -0.8f , -0.5f }, 100, &fly);
	path.PushBack({ -0.8f , 0.5f }, 100, &fly);
	collider = App->collisions->AddCollider({0, 0, 24, 24}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_BrownShip::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	Enemy::Update();
}
