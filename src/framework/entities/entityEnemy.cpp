#include "entityEnemy.h"
#include "entityMesh.h"
#include "framework/camera.h"
#include "graphics/mesh.h"
#include "graphics/shader.h"
#include "game/stage.h"
#include "game/world.h"

#include <algorithm>



void EntityEnemy::GetDamage(int damage) {
	health -= damage;
	if (health <= 0) {
		Die();
	}
}

void EntityEnemy::Die() {
	World::GetInstance()->removeEntity(this);

}
