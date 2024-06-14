#pragma once

#include "framework/includes.h"
#include "framework/framework.h"
#include "entityCollider.h"
#include "graphics/material.h"
#include "game/stage.h"



class Camera;
class Mesh;
class Material;
class World;

enum EnemyType {
    NORMAL,
    STRONG,
    FAST
};


class EntityEnemy : public EntityCollider {

public:

    EntityEnemy() {};
    EntityEnemy(EnemyType type);

    void render();
    void update(float seconds_elapsed);
    void GetDamage(int damage);
    void Die();
    void Eliminate();

    float velocity = 1;
    int maxHealth = 10;
    int health = 10;
    int waypoint_index = 0;
    
    EntityUI* vida;
    Material vida_m;
   
};

