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



class EntityProjectile : public EntityCollider {

public:

    EntityProjectile() {};
    EntityProjectile(Mesh* mesh, const Material& material) : EntityCollider(mesh, material) {
    };

    void update(float seconds_elapsed) override;

    EntityEnemy* objective;
    float speed = 5.0;


    // Methods overwritten from base class
    //void render(Camera* camera) override;
    //void update(float elapsed_time);
};

