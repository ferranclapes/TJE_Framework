#pragma once

#include "framework/includes.h"
#include "framework/framework.h"
#include "framework/entities/entityMesh.h"

class Mesh;
class Material;

class EntityCollider : public EntityMesh {
    
public:
    
    EntityCollider() {};
    EntityCollider(Mesh* mesh, const Material& material) : EntityMesh(mesh, material) {
        
    }
    
    bool is_dynamic = false;
    
    // New methods
    //bool testCollision();
    
};

