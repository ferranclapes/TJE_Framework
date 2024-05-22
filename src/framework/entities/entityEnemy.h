#pragma once

#include "framework/includes.h"
#include "framework/framework.h"
#include "entityCollider.h"
#include "graphics/material.h"
#include "game/stage.h"

class Camera;
class Mesh;
class Material;



class EntityEnemy : public EntityCollider {

public:

    EntityEnemy() {};
    EntityEnemy(Mesh* mesh, const Material& material) : EntityCollider(mesh, material) {
    };

    void GetDamage(int damage);
    void Die();

    float velocity = 1;
    int health = 10;

    // Methods overwritten from base class
    //void render(Camera* camera) override;
    //void update(float elapsed_time);
};
