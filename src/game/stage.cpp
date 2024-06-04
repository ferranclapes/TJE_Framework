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
#include "framework/entities/entityTower.h"
#include "framework/entities/entityEnemy.h"
#include "game/game.h"
#include "graphics/mesh.h"

void Stage::render()
{
    
}

void Stage::update(float seconse_elapsed)
{
    
}

// INTRO STAGE
IntroStage::IntroStage() {
    
}

void IntroStage::render()
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

void PlayStage::render()
{
    drawText(50, 50, std::to_string(money), Vector3(1, 0, 0), 5);
    for (EntityEnemy* e : World::GetInstance()->enemies) {
        drawText(100, 100, std::to_string(e->health), Vector3(1, 1, 1), 5);
    }

    World::GetInstance()->render(Camera::current);
}


void PlayStage::update(float seconds_elapsed)
{
    
    if(Input::isMousePressed(SDL_BUTTON_LEFT))
    {
        PlaceTower();
    }
    if (Input::isKeyPressed(SDL_SCANCODE_1)) {
        towerType = "towerRound_sampleA.obj";
        typeToPlace = MINE;
    }
    if (Input::isKeyPressed(SDL_SCANCODE_2)) {
        towerType = "weapon_ballista.obj";
        typeToPlace = BALLISTA;
    }
    if (Input::isKeyPressed(SDL_SCANCODE_3)) {
        towerType = "weapon_catapult.obj";
        typeToPlace = CATAPULT;
    }

    if (int(Game::instance->time) % 2 == 0 && !moneyCounted) {
        money += 2 * numMines;
        moneyCounted = true;
    }
    if (int(Game::instance->time) % 2 == 1 && moneyCounted) {
        moneyCounted = false;
    }


    if (waveTimeOut <= 0 && nextWave) {
        std::getline(enemyWaves, waves);
        iter = 0;
        waveTimeOut = 2;
        nextWave = false;
    }
    else if(nextWave) {
        waveTimeOut -= seconds_elapsed;
    }
    if (waves != "a") {
        if (timeOut <= 0) {
            if (waves[iter] == 'N') {
                EntityEnemy* new_enemy = new EntityEnemy(NORMAL);
                World::GetInstance()->addEntity(new_enemy);
                World::GetInstance()->enemies.emplace_back(new_enemy);
                timeOut += 1;
            }
            else if (waves[iter] == 'S') {
                EntityEnemy* new_enemy = new EntityEnemy(STRONG);
                World::GetInstance()->addEntity(new_enemy);
                World::GetInstance()->enemies.emplace_back(new_enemy);
                timeOut += 2;
            } 
            else if (waves[iter] == 'F') {
                EntityEnemy* new_enemy = new EntityEnemy(FAST);
                World::GetInstance()->addEntity(new_enemy);
                World::GetInstance()->enemies.emplace_back(new_enemy);
                timeOut += 0.7;
            }
            else if (waves[iter] == '\0') {
                waves = "a";
                nextWave = true;
            }
            iter++;
        }
        timeOut -= seconds_elapsed;
    }

    World::GetInstance()->update(seconds_elapsed);
}

void PlayStage::PlaceTower() {
    Camera* camera = Camera::current;

    //Get ray direction
    Vector2 mouse_pos = Input::mouse_position;
    Vector3 ray_origin = camera->eye;
    Vector3 ray_direction = camera->getRayDirection(mouse_pos.x, mouse_pos.y, Game::instance->window_width, Game::instance->window_height);


    // Fill collision vector
    std::vector<Vector3> collisions;
    std::vector<EntityMesh*> entitymeshes;

    for (Entity* e : World::GetInstance()->root->children)
    {
        EntityCollider* collider = dynamic_cast<EntityCollider*>(e);

        if (!collider)
        {
            continue;
        }

        Vector3 col_point;
        Vector3 col_norm;

        if (collider->mesh->testRayCollision(collider->model, ray_origin, ray_direction, col_point, col_norm)) //ray_direction
        {
            EntityTower* tower = dynamic_cast<EntityTower*>(collider);

            if (!tower || tower->towerType != EMPTY) {
                continue;
            }


            if (typeToPlace == MINE) {
                if (money >= 10) {
                    money -= 10;
                    tower->ammo = 10;
                }
                else {
                    continue;
                }
            }
            else if(typeToPlace == BALLISTA) {
                if (money >= 5) {
                    money -= 5;
                    tower->ammo = 10;
                }
                else {
                    continue;
                }
            }
            else if (typeToPlace == CATAPULT) {
                if (money >= 8) {
                    money -= 8;
                    tower->ammo = 7;
                }
                else {
                    continue;
                }
            }

            tower->towerType = typeToPlace;
            if (tower->isMine && typeToPlace == MINE) {
                numMines++;
            }

            //si xoca amb algu fico a dins
            entitymeshes.push_back(dynamic_cast<EntityMesh*>(e));
        }
    }
    //Generate entities
    for (auto& emesh : entitymeshes)
    {
        std::string meshPath = std::string("data/Kenney/Models/OBJ format/") + std::string(towerType);
        Mesh* mesh = Mesh::Get(meshPath.c_str());
        EntityMesh* new_entity = new EntityMesh(mesh, {});
        new_entity->model.setTranslation(Vector3(0, 0, -0.2));
        new_entity->model.rotate(PI / 2, Vector3(1, 0, 0));
        //World::GetInstance()->addEntity(new_entity);
        emesh->addChild((Entity*) new_entity);
    }
}

void PlayStage::onExit()
{
    
}

void PlayStage::onEnter()
{
    enemyWaves.open("data/EnemyWaves.txt", std::ios::in);
}




// END STAGE
    
EndStage::EndStage()
{

       
}

void EndStage::render()
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

