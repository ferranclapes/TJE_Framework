//
//  entityUI.hpp
//  TJE_Framework
//
//  Created by Alba Arcos on 22/5/24.
//

#ifndef entityUI_hpp
#define entityUI_hpp

#include <stdio.h>

#include "framework/entities/entityMesh.h"

#endif /* entityUI_hpp */


#include "framework/camera.h"
#include "graphics/mesh.h"
#include "graphics/shader.h"
#include "graphics/material.h"
#include "game/game.h"
#include "game/world.h"


//class Mesh;
//class Camera;
//class Shader;
//class Material;

class EntityUI : public EntityMesh {
    
public:
    
    EntityUI();
    EntityUI(Mesh* mesh, const Material& material);
    //EntityUI(Vector2 size, conts Material& material);
    
    Mesh* mesh = nullptr;
    Material material;
    
    int mask;
    bool visible;
    Vector2 position;
    
    
    void render(Camera* camera2d);
    void update(float seconds_elapsed);
    void update3D(Vector3 position3d);
    
    
    // EntityUI(Vector2 size, conts Material& material); //simplificiacio
    // EntityUI(Vector2 pos, Vector2 size, const Material&, eButtonId button_id, );
    
    
};

