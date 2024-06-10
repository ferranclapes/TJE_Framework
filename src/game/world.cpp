#include "world.h"
#include <fstream>
#include "framework/utils.h"
#include "graphics/material.h"
#include "framework/entities/entityMesh.h"
#include "framework/entities/EntityCollider.h"
#include "graphics/mesh.h"
#include "framework/camera.h"
#include "framework/entities/entityTower.h"
#include "framework/entities/entityEnemy.h"
#include "framework/entities/entityUI.h"

World* World::instance = nullptr;

World::World()
{
    root = new Entity();
    instance = this;
    parseScene("data/maps/myscene.scene", root);
}

void World::render(Camera* camera)
{

    root->render(camera);
}

void World::update(float seconds_elapsed)
{
    root->update(seconds_elapsed);
}

World* World::GetInstance() {
    if (instance == nullptr) {
        return new World();
    }
    return instance;
}

void World::addEntity(Entity* new_entity) {
    root->addChild(new_entity);
}

void World::removeEntity(Entity* e) {
    root->removeChild(e);
}

void World::RemoveEnemy(EntityEnemy* enemy) {
    auto it = std::find(enemies.begin(), enemies.end(), enemy);
    enemies.erase(it);

}

bool World::parseScene(const char* filename, Entity* root)
{
    std::cout << " + Scene loading: " << filename << "..." << std::endl;

    std::ifstream file(filename);

    if (!file.good()) {
        std::cerr << "Scene [ERROR]" << " File not found!" << std::endl;
        return false;
    }

    std::string scene_info, mesh_name, model_data;
    file >> scene_info; file >> scene_info;
    int mesh_count = 0;

    std::map<std::string, sRenderData> meshes_to_load;

    // Read file line by line and store mesh path and model info in separated variables
    while (file >> mesh_name >> model_data)
    {
        if (mesh_name[0] == '#')
            continue;

        // Get all 16 matrix floats
        std::vector<std::string> tokens = tokenize(model_data, ",");

        // Fill matrix converting chars to floats
        Matrix44 model;
        for (int t = 0; t < tokens.size(); ++t) {
            model.m[t] = (float)atof(tokens[t].c_str());
        }

        // Add model to mesh list (might be instanced!)
        sRenderData& render_data = meshes_to_load[mesh_name];
        render_data.models.push_back(model);
        mesh_count++;
    }

    // Iterate through meshes loaded and create corresponding entities
    for (auto data : meshes_to_load) {

        mesh_name = "data/maps/" + data.first;
        sRenderData& render_data = data.second;

        // No transforms, nothing to do here
        if (render_data.models.empty())
            continue;


        Material mat = render_data.material;
        EntityMesh* new_entity = nullptr;

        size_t tag = data.first.find("clickable");
        //tag per crear cami:
        size_t wp_tag = data.first.find("waypoint");

        if (tag != std::string::npos) {
            Mesh* mesh = Mesh::Get(mesh_name.c_str());
            // Create a different type of entity
            size_t mine = data.first.find("mine");
            if (mine != std::string::npos) {
                new_entity = new EntityTower(mesh, mat, true);
            }
            else {
                new_entity = new EntityTower(mesh, mat, false);
            }
        }
        else if(wp_tag != std::string::npos){
            waypoints.push_back(render_data.models[0].getTranslation());
            
        }
        else {
            Mesh* mesh = Mesh::Get(mesh_name.c_str());
            new_entity = new EntityCollider(MAP, mesh, mat);
        }

        if (!new_entity) {
            continue;
        }

        new_entity->name = data.first;

        // Create instanced entity
        if (render_data.models.size() > 1) {
            new_entity->isInstanced = true;
            new_entity->models = render_data.models; // Add all instances
        }
        // Create normal entity
        else {
            new_entity->model = render_data.models[0];
        }

        // Add entity to scene root
        root->addChild(new_entity);
    }
    std::cout << "Scene [OK]" << " Meshes added: " << mesh_count << std::endl;

    return true;
}

