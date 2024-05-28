#include "entityProjectile.h"
#include "entityTower.h"
#include "entityMesh.h"
#include "framework/camera.h"
#include "graphics/mesh.h"
#include "graphics/shader.h"
#include "framework/entities/entityEnemy.h"
#include "game/world.h"

#include <algorithm>


void EntityProjectile::update(float seconds_elapsed) {
	Vector3 translation = Vector3(objective->model.getTranslation() - model.getTranslation());
	translation = translation.normalize() * speed * seconds_elapsed;
	model.translate(translation.x, translation.y, translation.z);

}
