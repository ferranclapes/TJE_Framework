#include "entityTower.h"
#include "entityMesh.h"
#include "framework/camera.h"
#include "graphics/mesh.h"
#include "graphics/shader.h"
#include "framework/entities/entityEnemy.h"

#include <algorithm>


void EntityTower::FindEnemies(std::vector<EntityEnemy*> enemies) {
	float min_distance = distance;
	EntityEnemy* closest = NULL;
	for (EntityEnemy* enemy : enemies) {
		if (enemy->distance(this) < min_distance) {
			min_distance = enemy->distance(this);
			closest = enemy;
		}
	}

	if (closest) {
		Shoot(closest);
	}
}

void EntityTower::Shoot(EntityEnemy* enemy) {
	enemy->GetDamage(damage);
}