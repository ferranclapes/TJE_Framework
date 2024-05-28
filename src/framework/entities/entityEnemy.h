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

    void update(float seconds_elapsed);
    void GetDamage(int damage);
    void Die();
    void followPath(float seconds_elapsed);

    float velocity = 1;
    int health = 10;
    int waypoint_index = 0;
    
   
};

