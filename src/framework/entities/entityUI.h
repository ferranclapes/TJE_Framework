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
class Material;

enum eButon{
    PLAY,
    EXIT
};

class EntityUI : public EntityMesh {
    
public:
    
    EntityUI(float center_x, float center_y, float w, float h, const Material& material);// eButon buton_id);
    
    
    float pos_x;
    float pos_y;
    float width;
    float height;
    Material material;
    //EntityUI(Vector2 size, conts Material& material);
    
    //Mesh* mesh = nullptr;
   // Material material;
    
   
    Mesh* quad;
    
    float mask;
    bool visible;
    Vector2 position;
    
    
    void render(Camera* camera2d) override;
    void update(float seconds_elapsed) override;
    
    
    // EntityUI(Vector2 size, conts Material& material); //simplificiacio
    // EntityUI(Vector2 pos, Vector2 size, const Material&, eButtonId button_id, );
    
    
};

