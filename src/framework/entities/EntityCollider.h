#pragma once

#include "framework/includes.h"
#include "framework/framework.h"
#include "framework/entities/entityMesh.h"
#include "framework/extra/coldet/coldet.h"

class Mesh;
class Material;

enum ColliderType {
    MAP = 1,
    TOWER = 2,
    PROJECTILE = 3
};

class EntityCollider : public EntityMesh {
    
public:
    
    EntityCollider() {};
    EntityCollider(int type, Mesh* mesh, const Material& material) : EntityMesh(mesh, material) {
        coliderType = type;
        if (type == MAP) {
            is_dynamic = false;
        }
        else {
            is_dynamic = true;
        }
    }
    



    bool is_dynamic = false;
    int coliderType = 0;
    
    // New methods
    //bool testCollision();
    
};

