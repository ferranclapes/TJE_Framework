#pragma once

#include "framework/includes.h"
#include "framework/framework.h"
#include "framework/entities/entityMesh.h"
//#include "framework/entities/etityMesh.h"

class EntityCollider : public EntityMesh {
    
public:
    
    
    bool is_dynamic = false;
    
    // New methods
    bool testCollision();
    
};

