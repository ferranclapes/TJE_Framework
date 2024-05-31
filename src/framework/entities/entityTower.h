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



class EntityTower : public EntityCollider {

public:

    EntityTower() {};
    EntityTower(Mesh* mesh, const Material& material, bool im) : EntityCollider(TOWER, mesh, material) {
        isMine = im;
    };

    void update(float seconds_elapsed) override;

    void FindEnemies(float sec_ela);
    void Shoot(EntityEnemy* enemy);
    float Aim(EntityEnemy* enemy, float sec_ela);

    bool isMine = false;
    int towerType = EMPTY;
    float distance = 5.0;
    int damage = 2;
    float cooldown = 1.0;
    float timeToShoot = 0.0;


    // Methods overwritten from base class
    //void render(Camera* camera) override;
    //void update(float elapsed_time);
};

