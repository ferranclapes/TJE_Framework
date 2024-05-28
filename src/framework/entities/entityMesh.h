#pragma once

#include "framework/includes.h"
#include "framework/framework.h"
#include "entity.h"
#include "graphics/material.h"

class Mesh;
class Camera;
class Texture;
class Shader;
class Material;

class EntityMesh : public Entity {

public:

    EntityMesh();
    EntityMesh(Mesh* mesh, const Material& material);
    
    void SetMesh(Mesh* mes, const Material& mat) {
        mesh = mes;
        material = mat;
    }

    // Attributes of the derived class
    Mesh* mesh = nullptr;    
    Material material;
    
    bool isInstanced = false;
    std::vector<Matrix44> models; //vector de models de qunates vegades rendaritzes i a on

    // Methods overwritten from base class
    void render(Camera* camera) override;
    void update(float elapsed_time);
};

