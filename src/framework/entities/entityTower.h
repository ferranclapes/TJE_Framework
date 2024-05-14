#pragma once

#include "framework/includes.h"
#include "framework/framework.h"
#include "entityCollider.h"
#include "graphics/material.h"

class Camera;
class Mesh;
class Material;

class EntityTower : public EntityCollider {

public:

    EntityTower();
    EntityTower(Mesh* mesh, const Material& material) {
        EntityCollider(mesh, material);
    }


    // Methods overwritten from base class
    //void render(Camera* camera) override;
    //void update(float elapsed_time);
};

