#include "Particle.h"
#include "Application.h"
#include "Collider.h"
#include "ModuleParticles.h"

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : anim(p.anim), position(p.position), speed(p.speed),
										frameCount(p.frameCount), lifetime(p.lifetime)
{

}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

bool Particle::Update()
{
	bool ret = true;
	frameCount++;

	// The particle is set to 'alive' when the delay has been reached
	if (!isAlive && frameCount >= 0)
		isAlive = true;

	if (isAlive)
	{
		anim.Update();

		// If the particle has a specific lifetime, check when it has to be destroyed
		if (lifetime > 0)
		{
			if (frameCount >= lifetime)
				ret = false;
		}
		// Otherwise the particle is destroyed when the animation is finished
		else if (anim.HasFinished()) {
			
			if (collider != nullptr && collider->type == ROUND_BOMB) {
				
				App->particles->AddParticle(App->particles->subshot1, position.x, position.y, ColliderType::ROUND_BOMB);
				App->particles->AddParticle(App->particles->subshot2, position.x, position.y, ColliderType::ROUND_BOMB);
				App->particles->AddParticle(App->particles->subshot3, position.x, position.y, ColliderType::ROUND_BOMB);
				App->particles->AddParticle(App->particles->subshot4, position.x, position.y, ColliderType::ROUND_BOMB);
				App->particles->AddParticle(App->particles->subshot5, position.x, position.y, ColliderType::ROUND_BOMB);
				App->particles->AddParticle(App->particles->subshot6, position.x, position.y, ColliderType::ROUND_BOMB);
				App->particles->AddParticle(App->particles->subshot7, position.x, position.y, ColliderType::ROUND_BOMB);
				App->particles->AddParticle(App->particles->subshot8, position.x, position.y, ColliderType::ROUND_BOMB);
				
			}

			if (collider != nullptr && collider->type == CLAW) {
				App->particles->AddParticle(App->particles->g_claw_o, position.x, position.y, ColliderType::CLAW);
			}
						

			ret = false;
		}
		// Update the position in the screen
		position.x += speed.x;
		position.y += speed.y;

		if (collider != nullptr)
			collider->SetPos(position.x, position.y);
	}

	return ret;
}

void Particle::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}