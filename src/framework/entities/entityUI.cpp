//
//  entityUI.cpp
//  TJE_Framework
//
//  Created by Alba Arcos on 22/5/24.
//

#include "entityUI.h"

EntityUI::EntityUI()
{


    Mesh* quad = new Mesh();
    quad->vertices.push_back(Vector3(-1, 1, 0));
    quad->uvs.push_back(Vector2(0, 1));
    quad->vertices.push_back(Vector3(-1, -1, 0));
    quad->uvs.push_back(Vector2(0, 0));
    quad->vertices.push_back(Vector3(1, -1, 0));
    quad->uvs.push_back(Vector2(1, 0));


    quad->vertices.push_back(Vector3(1, -1, 0));
    quad->uvs.push_back(Vector2(1, 0));
    quad->vertices.push_back(Vector3(1, -1, 0));
    quad->uvs.push_back(Vector2(1, 0));
    quad->vertices.push_back(Vector3(1, 1, 0));
    quad->uvs.push_back(Vector2(1, 1));

    this->mesh = quad;

    this->material = material;
}
/*EntityUI::EntityUI(Vector2 size, conts Material& material)
{
    this->material = material;
    //size??
    
}*/
void EntityUI::render(Camera* camera2d)
{
    
     std::cout << "render entityUI" << std::endl;
     //com el render d'entity mesh pero canviant camera
    glDisable( GL_DEPTH_TEST );
    glDisable( GL_CULL_FACE );
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
     
     for (int i = 0; i < children.size(); ++i) {
         children[i]->render(camera2d);
     }
    
     // Get the last camera that was activated
     //Camera* camera = Camera::current;
     if (!material.shader) {
         material.shader = Shader::Get("data/shaders/helth_bar.vs" , "data/shaders/helth_bar.fs");
     }
     // Enable shader and pass uniforms
     material.shader->enable();
     if(!isInstanced){
     material.shader->setUniform("u_model", getGlobalMatrix());
     }
     
     //update uniforms
     material.shader->setUniform("u_color", material.color);
     material.shader->setUniform("u_viewprojection", camera2d->viewprojection_matrix);
     material.shader->setUniform("u_mask", mask); //afegit
    
     if (material.diffuse){
     material.shader->setTexture("u_texture", material.diffuse, 0);
     }
     // Render the mesh using the shader
         if (!isInstanced) {
             mesh->render(GL_TRIANGLES);
         }
         else {
             mesh->renderInstanced(GL_TRIANGLES, models.data(), models.size());
         }
         // Disable shader after finishing rendering
         material.shader->disable();
         
         
         
         //World* world = World::get_instance(); ?
         
         
         //tornar a deixar com estven
         glDisable(GL_BLEND);
         glEnable(GL_DEPTH_TEST);
         
}

void EntityUI::update(float seconds_elapsed)
{
   
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
         
     Vector3 pos3d = position3d;
        
    //Updarte 3dHUD
        
    int width = Game::instance->window_width;
    int height = Game::instance->window_height;
    Game* game = Game::instance;
    // ELS TENEN LA CAMERA A WORLD
    
    visible = true;
         
    Vector3 pos = game->camera->project(position3d, width, height);
    
    if(pos.z < 0.0f || pos.z > 1.0f){ //si no esta entre 0 i 1 no es veu
        visible = false;
    }else{
        pos.y = height - pos.y;
        position = Vector2(pos.x, pos.y);
    }
}

             

