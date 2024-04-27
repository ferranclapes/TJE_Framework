#include "entityMesh.h"
#include "framework/camera.h"
#include "graphics/mesh.h"
#include "graphics/material.h"
#include "graphics/shader.h"

#include <algorithm>

void EntityMesh::render() {

    // Get the last camera that was activated
    Camera* camera = Camera::current;

    // Enable shader and pass uniforms
    material.shader->enable();
    if(!isInstanced){
        
        material.shader->setUniform("u_model", getGlobalMatrix());

    }
    
    //update uniforms
    material.shader->setUniform("u_color", material.color)
    shader->setUniform("u_viewproj", camera->viewprojection_matrix);
    shader->setTexture("u_texture", texture );


    // Render the mesh using the shader
    mesh->render( GL_TRIANGLES );

    // Disable shader after finishing rendering
    shader->disable();
};

void EntityMesh::update(<#float elapsed_time#>){
    
}

