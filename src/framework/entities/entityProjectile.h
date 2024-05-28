#pragma once

#include "framework/includes.h"
#include "framework/framework.h"
#include "entityCollider.h"
#include "graphics/material.h"
#include "game/stage.h"

class Camera;
class Mesh;
class Material;
class EntityEnemy;

enum ProjectileType {
    ARROW,
    STONE
};

class EntityProjectile : public EntityCollider {

public:

    EntityProjectile() {};
    EntityProjectile(ProjectileType ty, EntityEnemy* obj, float da, Mesh* mesh, const Material& material);

    void update(float seconds_elapsed) override;

    EntityEnemy* objective = NULL;
    float speed = 150.0;
    float damage = 2;
    int type = 0;

    //Only for stones
    Vector3 target = Vector3(0,0,0);
    float maxHeigh = 2.0f;
    float verticalVelocity = 0;


    // Methods overwritten from base class
    //void render(Camera* camera) override;
    //void update(float elapsed_time);
};

