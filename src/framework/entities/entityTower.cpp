#include "entityTower.h"
#include "entityMesh.h"
#include "entityProjectile.h"
#include "framework/camera.h"
#include "graphics/mesh.h"
#include "graphics/shader.h"
#include "framework/entities/entityEnemy.h"
#include "game/world.h"
#include "game/game.h"

#include <algorithm>


void EntityTower::update(float seconds_elapsed) {
	if (towerType != MINE && towerType != EMPTY) {
		FindEnemies(seconds_elapsed);
		if (timeToShoot <= 0) {
		}
		else {
			timeToShoot -= seconds_elapsed;
		}
	}
	else if (towerType == MINE) {
		ammo -= seconds_elapsed;
		if (ammo <= 0) {
			EliminateTower();
		}
	}
}

void EntityTower::FindEnemies(float sec_ela) {
	float min_distance = distance;
	EntityEnemy* closest = NULL;
	for (EntityEnemy* enemy : World::GetInstance()->enemies) {
		if (enemy->distance(this) < min_distance) {
			min_distance = enemy->distance(this);
			closest = enemy;
		}
	}

	if (closest) {
		float angle = Aim(closest, sec_ela);
		if (timeToShoot <= 0 && angle <= PI/2) {
			Shoot(closest);
			timeToShoot = cooldown;
		}
	}
}

void EntityTower::Shoot(EntityEnemy* enemy) {
	
	if (towerType == BALLISTA) {
		ammo -= 1;
		std::string meshPath = std::string("data/objects/arrow3.obj");
		Mesh* mesh = Mesh::Get(meshPath.c_str());
		EntityProjectile* projectile = new EntityProjectile(ARROW, enemy, damage, mesh, {});
		projectile->model.setTranslation(model.getTranslation());
		float angle = projectile->model.getYawRotationToAimTo(enemy->model.getTranslation());
		projectile->model.rotate(angle, Vector3(0, 1, 0));
		projectile->model.scale(0.08, 0.08, 0.08);
		World::GetInstance()->addEntity(projectile);
	}
	else if (towerType == CATAPULT) {
		ammo -= 1;
		std::string meshPath = std::string("data/objects/stone.obj");
		Mesh* mesh = Mesh::Get(meshPath.c_str());
		EntityProjectile* projectile = new EntityProjectile(STONE, enemy, damage, mesh, {});
		projectile->model.setTranslation(model.getTranslation());
		float angle = projectile->model.getYawRotationToAimTo(enemy->model.getTranslation());
		projectile->model.rotate(angle, Vector3(0, 1, 0));
		projectile->model.scale(0.2, 0.2, 0.2);
		World::GetInstance()->addEntity(projectile);
	}

	if (ammo <= 0) {
		EliminateTower();
	}

}

float EntityTower::Aim(EntityEnemy* enemy, float sec_ela) {
	float angle = model.getYawRotationToAimTo(enemy->model.getTranslation());
	model.rotate(angle * sec_ela, Vector3(0, 0, -1));
	return angle;
}


void EntityTower::EliminateTower() {
	for (auto child : this->children) {
		auto it = std::find(this->children.begin(), this->children.end(), child);
		this->children.erase(it);
		delete child;
		if (towerType == MINE) {
			PlayStage* stage = dynamic_cast<PlayStage*>(Game::GetInstance()->current_stage);
			stage->numMines -= 1;
		}
	}
	towerType = EMPTY;
}
