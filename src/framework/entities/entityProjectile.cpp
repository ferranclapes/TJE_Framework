#include "entityProjectile.h"
#include "entityTower.h"
#include "entityMesh.h"
#include "framework/camera.h"
#include "graphics/mesh.h"
#include "graphics/shader.h"
#include "framework/entities/entityEnemy.h"
#include "game/world.h"

#include <algorithm>


EntityProjectile::EntityProjectile(ProjectileType ty, EntityEnemy* obj, float da, Mesh* mesh, const Material& material) : EntityCollider(PROJECTILE, mesh, material) {
    objective = obj;
    damage = da;
    type = ty;
    if (type == ARROW) {
        speed = 150;
        damage = 1;
    }
    else if (type == STONE) {
        speed = 10.0;
        damage = 20;
        target = Vector3(obj->model.getTranslation().x, 0, obj->model.getTranslation().z);
        float horizontalDistance = Vector3(model.getTranslation().x, 0, model.getTranslation().z).distance(target);
        float totalTime = horizontalDistance / speed;
        verticalVelocity = 10;
    }
};

void EntityProjectile::update(float seconds_elapsed) {
    if (type == ARROW) {
        model.translate(0, 0, speed * seconds_elapsed);

        float distance_to_target = model.getTranslation().distance(objective->model.getTranslation());
        if (distance_to_target < 0.7f) {
            objective->GetDamage(damage);
            World::GetInstance()->removeEntity(this);
            delete this;
        }

    }
    else if (type == STONE) {
        

        float distance_to_target = model.getTranslation().distance(target);
        std::cout << "Distance to target = " << distance_to_target << "\n";
        if (distance_to_target < 0.7f) {
            objective->GetDamage(damage);
            World::GetInstance()->removeEntity(this);
            delete this;
        }
    }
}
