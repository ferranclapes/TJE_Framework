#include "entityTower.h"
#include "entityMesh.h"
#include "framework/camera.h"
#include "graphics/mesh.h"
#include "graphics/shader.h"
#include "framework/entities/entityEnemy.h"
#include "game/world.h"

#include <algorithm>


void EntityTower::update(float seconds_elapsed) {
	if (towerType == BALLISTA) {
		if (timeToShoot <= 0) {
			FindEnemies();
			timeToShoot = cooldown;
		}
		else {
			timeToShoot -= seconds_elapsed;
		}
	}
}

void EntityTower::FindEnemies() {
	float min_distance = distance;
	EntityEnemy* closest = NULL;
	for (EntityEnemy* enemy : World::GetInstance()->enemies) {
		if (enemy->distance(this) < min_distance) {
			min_distance = enemy->distance(this);
			closest = enemy;
		}
	}

	if (closest) {
		Aim(closest);
		Shoot(closest);
	}
}

void EntityTower::Shoot(EntityEnemy* enemy) {
	enemy->GetDamage(damage);
}

void EntityTower::Aim(EntityEnemy* enemy) {

}