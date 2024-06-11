/*  by Javi Agenjo 2013 UPF  javi.agenjo@gmail.com
	This contains several functions that can be useful when programming your game.
*/
#pragma once
#include "includes.h"
#include "utils.h"
#include "entities/entity.h"
#include "entities/entityMesh.h"

#include <vector>


class Particle : public EntityMesh {
public:
	bool isdead = false;

	Vector3 position;
	Vector3 velocity;
	float ttl;

	float size;
	Vector3 color;
	float alpha;


	void update(float sec_ela) override;
	void destroy();


};


class ParticleEmiter : public Entity {
	int max_particles = 300;
	int active_particles = 0;
	// Particle container
	std::vector<Particle> particles;

	// Properties of the emitter
	int last_id = 0;
	float emit_rate;
	float emit_timer;

	// Properties of the particles
	float max_ttl;
	std::vector<Vector3> sizes;
	std::vector<float> alphas;
	Texture* texture = nullptr;
	bool additive_blending;

	void emit();

public:

	ParticleEmiter();

	void render();
	void update(float seconds_elapsed);

};


