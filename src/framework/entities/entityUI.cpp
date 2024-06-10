//
//  entityUI.cpp
//  TJE_Framework
//
//  Created by Alba Arcos on 22/5/24.
//

#include "entityUI.h"
#include "framework/input.h"


EntityUI::EntityUI(float center_x, float center_y, float w, float h, const Material& material) // eButon buton_id)
{
    
    this->pos_x = center_x;
    this->pos_y = center_y;
    this->width = w;
    this->height = h;
    this->material = material;
    
    quad = new Mesh();
    quad->createQuad(center_x, center_y, w, h, false);
    
    if (!this->material.shader) {
        this->material.shader = Shader::Get("data/shaders/example.vs" , "data/shaders/boto.fs");
    }
}


void EntityUI::render(Camera* camera2D)
{
    
    // Set the camera as default
    camera2D->enable();
    
        // Set flags
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    
    for (int i = 0; i < children.size(); ++i) {
        children[i]->render(camera2D);
    }
    
    material.shader->enable();

        // Upload uniforms
    material.shader->setUniform("u_color", material.color);
    material.shader->setUniform("u_viewprojection", camera2D->viewprojection_matrix);
    material.shader->setUniform("u_mask", mask);
    //material.shader->setUniform("u_texture", material.diffuse, 0);
    
            // Do the draw call
    quad->render( GL_TRIANGLES );

            // Disable shader
    material.shader->disable();
    
    
        //tornar a deixar com estven
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    
    

}

void EntityUI::update(float seconds_elapsed)
{
 
    Vector2 mouse_pos = Input::mouse_position;
    
    if(mouse_pos.x > (this->pos_x - this->width * 0.5f) &&
       mouse_pos.x < (this->pos_x + this->width * 0.5f) &&
       mouse_pos.y > (this->pos_y - this->height * 0.5f) &&
       mouse_pos.y< (this->pos_y + this->height * 0.5f))
    {
        
        // Si el mpouse esta dins del button
        material.color = Vector4(1, 0, 0, 0);
    }
    
    if(Input::isKeyPressed(SDL_SCANCODE_A)){
        std::cout << "start press" << std::endl;
    }
    /*Vector2 mouse_pos = Input::mouse_position;
    
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
    }*/
}
void EntityUI::update3D(Vector3 position3d){
         
     //Vector3 pos3d = position3d;
        
    //Updarte 3dHUD
        
   // int width = Game::instance->window_width;
    //int height = Game::instance->window_height;
    Game* game = Game::instance;
    
    
    visible = true;
         
    Vector3 pos = game->camera2D->project(position3d, width, height);
    
    if(pos.z < 0.0f || pos.z > 1.0f){ //si no esta entre 0 i 1 no es veu
        visible = false;
    }else{
        pos.y = height - pos.y;
        position = Vector2(pos.x, pos.y);
    }

}

             

