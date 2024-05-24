//
//  entityUI.cpp
//  TJE_Framework
//
//  Created by Alba Arcos on 22/5/24.
//

#include "entityUI.hpp"

/*EntityUI::EntityUI(){
    
}

void Entity::render(Camera* camera2d){
    //com el render d'entity mesh pero canviant camera
    
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    material.shader->enable();
    
    World* world = World::get_instance();
    
    
    
    
    
    
    //tornar a deixar com estven
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}


void EntityUI::update(float seconds_elapsed){
    Vector2 mouse_pos = Input::mouse_position;
    
    if(!visible){
        return
    }
    
    if(button_id != UndifinedButton &&
       mouse_pos.x > (position.x - size.x * 0.5f) &&
       mouse_pos.x < (position.x + size.x * 0.5f) &&
       mouse_pos.y > (position.y - size.y * 0.5f) &&
       mouse_pos.y< (position.y + size.y * 0.5f)){
        
        // Si el mpouse esta dins del button
        material.color = Vector4::BLUES;  //canvia de color x exemple color var 'u_color' que es passa al shader
        
        if(button)
    }
}



void EntityUI::update3D(Vector3 position3d){
    pos3d = position3d;
    
    //Updarte 3dHUD
    
    int with = Game:instance->window_with;
    int height = Gamme::
    World* world = World:get_instance();
    
    visible = true;
    
    Vector3 pos = world->camera->project(position3d, with, height); //en pixels
    
    if(pos.z < 0.0f || pos.z > 1.0f){ //si no esta entre 0 i 1 no es veu
        visible = false;
        
        
    }else{
        pos.y = height - pos.y;
        psoition = Vector2(pos.x, pos.y);
    }
}
*/
