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
    
    if (Camera::current->renderGUI == false) {
        return;
    }

    Camera* curr = Camera::current;
    // Set the camera as default
    camera2D->enable();
    
        // Set flags
    glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
    material.shader->setUniform("u_texture", material.diffuse);
    if(material.diffuse){
        material.shader->setTexture("u_texture", material.diffuse, 0);
    }
    
            // Do the draw call
    quad->render( GL_TRIANGLES );

            // Disable shader
    material.shader->disable();
    
    
        //tornar a deixar com estven
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    curr->enable();
    
}

void EntityUI::update(float seconds_elapsed)
{
 
    

}


             

