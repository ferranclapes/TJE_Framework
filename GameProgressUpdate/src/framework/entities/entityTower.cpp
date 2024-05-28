#include "entityTower.h"
#include "entityMesh.h"
#include "entityProjectile.h"
#include "framework/camera.h"
#include "graphics/mesh.h"
#include "graphics/shader.h"
#include "framework/entities/entityEnemy.h"
#include "game/world.h"

#include <algorithm>


void EntityTower::update(float seconds_elapsed) {
	if (towerType == BALLISTA) {
		FindEnemies();
		if (timeToShoot <= 0) {
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
		if (timeToShoot <= 0) {
			Shoot(closest);
			timeToShoot = cooldown;
		}
	}
}

void EntityTower::Shoot(EntityEnemy* enemy) {
	enemy->GetDamage(damage);

	/*std::string meshPath = std::string("data/objects/arrow2.obj");
	Mesh* mesh = Mesh::Get(meshPath.c_str());
	EntityProjectile* projectile = new EntityProjectile(mesh, {});
	projectile->model.setTranslation(model.getTranslation());
	float angle = projectile->model.getYawRotationToAimTo(enemy->model.getTranslation());
	projectile->model.rotate(angle, Vector3(0, 0, -1));
	World::GetInstance()->addEntity(projectile);*/


}

void EntityTower::Aim(EntityEnemy* enemy) {
	float angle = model.getYawRotationToAimTo(enemy->model.getTranslation());
	model.rotate(angle, Vector3(0, 0, -1));
}
