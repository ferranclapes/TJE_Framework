#include "entityProjectile.h"
#include "entityTower.h"
#include "entityMesh.h"
#include "framework/camera.h"
#include "graphics/mesh.h"
#include "graphics/shader.h"
#include "framework/entities/entityEnemy.h"
#include "game/world.h"

#include <algorithm>
#include <cmath>


EntityProjectile::EntityProjectile(ProjectileType ty, EntityEnemy* obj, float da, Mesh* mesh, const Material& material) : EntityCollider(PROJECTILE, mesh, material) {
    objective = obj;
    damage = da;
    type = ty;
    if (type == ARROW) {
        speed = 200;
        damage = 1;
    }
    else if (type == STONE) {
        Vector3 newTranslation = model.getTranslation();
        newTranslation.y = 0;
        model.setTranslation(newTranslation);
        damage = 20;
        target = Vector3(obj->model.getTranslation().x, 0, obj->model.getTranslation().z);
        float horizontalDistance = model.getTranslation().distance(target);
        speed = horizontalDistance / 0.55;
        verticalVelocity = 1.8;
    }
};

void EntityProjectile::update(float seconds_elapsed) {
    time += seconds_elapsed;
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
        if (time >= 0.55) {
            int x = 0;
        }
        else {
            float y = model.getTranslation().y;

            model.translate(0, verticalVelocity * time + (gravity / 2) * time * time, speed*0.005);
        }

        float distance_to_target = model.getTranslation().distance(target);
        if (distance_to_target < 0.7f) {
            objective->GetDamage(damage);
            World::GetInstance()->removeEntity(this);
            delete this;
        }
    }
}
