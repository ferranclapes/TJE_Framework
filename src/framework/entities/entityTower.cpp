#include "entityTower.h"
#include "entityMesh.h"
#include "framework/camera.h"
#include "graphics/mesh.h"
#include "graphics/shader.h"

#include <algorithm>



//
//void EntityTower::render(Camera* camera) {
//
//    // Get the last camera that was activated
//    //Camera* camera = Camera::current;
//
//    if (!material.shader) {
//        material.shader = Shader::Get(isInstanced ? "data/shaders/instanced.vs" : "data/shaders/basic.vs", "data/shaders/texture.fs");
//    }
//
//    // Enable shader and pass uniforms
//    material.shader->enable();
//    if(!isInstanced){
//        material.shader->setUniform("u_model", getGlobalMatrix());
//    }
//    
//    //update uniforms
//    material.shader->setUniform("u_color", material.color);
//    material.shader->setUniform("u_viewprojection", camera->viewprojection_matrix);
//
//    if (material.diffuse)
//        material.shader->setTexture("u_texture", material.diffuse, 0);
//
//
//    // Render the mesh using the shader
//    if (!isInstanced) {
//        mesh->render(GL_TRIANGLES);
//    }
//    else {
//        mesh->renderInstanced(GL_TRIANGLES, models.data(), models.size());
//
//    }
//
//    // Disable shader after finishing rendering
//    material.shader->disable();
//};
//
//void EntityTower::update(float elapsed_time){
//    
//}