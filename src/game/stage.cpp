//
//  stage.cpp
//  TJE_Framework
//
//  Created by Alba Arcos on 27/4/24.
//

#include "stage.h"
#include "framework/input.h"
#include "game/World.h"
#include "framework/entities/entity.h"
#include "framework/entities/EntityCollider.h"
#include "game/game.h"
#include "graphics/mesh.h"

void Stage::render(float seconse_elapsed)
{
    
}

void Stage::update(float seconse_elapsed)
{
    
}

// INTRO STAGE
IntroStage::IntroStage() {
    
}

void IntroStage::render(float seconse_elapsed)
{

}

void IntroStage::update(float seconse_elapsed)
{
    
}

void IntroStage::onExit()
{
    
}

void IntroStage::onEnter()
{
    
}


// PLAY STAGE
PlayStage::PlayStage()
{
    //loads
    
    //declarar variables com temps etc
   
}

void PlayStage::render(float time)
{
   
}

void PlayStage::update(float seconds_elapsed)
{
    World::GetInstance()->update();  //seconds elapsed?
    
    if(Input::isKeyPressed(SDL_SCANCODE_T))
    {
        Camera* camera = Camera::current;

        //Get ray direction
        Vector2 mouse_pos = Input::mouse_position;
        Vector3 ray_origin = camera->eye;
        Vector3 ray_direction = camera->getRayDirection(mouse_pos.x, mouse_pos.y, Game::instance->window_width, Game::instance->window_height);
        
        
        // Fill collision vector
        std::vector<Vector3> collisions;

        for (Entity* e: World::GetInstance()->root->children)
        {
            EntityCollider* collider = dynamic_cast<EntityCollider*>(e);
            
            if(!collider)
            {
                continue;
            }
            
            Vector3 col_point;
            Vector3 col_norm;
            
            if(collider->mesh->testRayCollision(collider->model, ray_origin, ray_direction, col_point, col_norm)) //ray_direction
            {
                //si xoca amb algu fico a dins
                collisions.push_back(col_point);
            }
        }
        //Generate entities
        for (auto& col_point : collisions)
        {
            Mesh* mesh = Mesh::Get("data/Kenney/Models/OBJ format/towerRound_roofA.obj");
            EntityMesh* new_entity = new EntityMesh(mesh, {});
            new_entity->model.setTranslation(col_point);
            World::GetInstance()->addEntity(new_entity);
        }
    }
}

void PlayStage::onExit()
{
    
}

void PlayStage::onEnter()
{
    
}

// END STAGE
    
EndStage::EndStage()
{

       
}

void EndStage::render(float seconse_elapsed)
{
    
    
}

void EndStage::update(float seconse_elapsed)
{
   
}

void EndStage::onExit()
{
    
}

void EndStage::onEnter()
{
    
}

