//
//  stage.cpp
//  TJE_Framework
//
//  Created by Alba Arcos on 27/4/24.
//


#include "stage.h"
#include "framework/input.h"
#include "game/world.h"
#include "framework/entities/entity.h"
#include "framework/entities/EntityCollider.h"
#include "framework/entities/entityTower.h"
#include "framework/entities/entityEnemy.h"
#include "framework/entities/entityUI.h"
#include "game/game.h"
#include "graphics/texture.h"
#include "graphics/shader.h"


Shader* shader = NULL;
Mesh* quad = NULL;
Texture* intro = NULL;
Material fons_m;
Material play_m;

void Stage::render()
{
   
    
}

void Stage::update(float seconse_elapsed)
{
    
}

// INTRO STAGE
IntroStage::IntroStage() {
    
    int width = Game::GetInstance()->window_width;
    int height = Game::GetInstance()->window_height;
    
    //Material fons_m;
    //fons_m.color = Vector4(0, 1, 0, 0);
    fons_m.shader = Shader::Get("data/shaders/example.vs", "data/shaders/image.fs");
    fons_m.diffuse = Texture::Get("data/textures/intro.png");
    fons = new EntityUI(0.0f, 0.0f, width, height, fons_m);
    
    //Material play_m;
    play_m.color = Vector4(1, 1, 1, 1);
    //play_m.diffuse = Texture::Get("data/textures/blanc.png");
    play = new EntityUI(0.0f, 0.0f, 0.5f, 0.2f, play_m);
    
    fons->addChild(play);
}
    

void IntroStage::render()
{
   
    fons->render(Game::GetInstance()->camera2D);
    drawText(180, 140, "Guardians del castell", Vector3(0, 0, 0), 4);
    drawText(365, 290, "Start", Vector3(0, 0, 0), 3);
    
}

void IntroStage::update(float seconse_elapsed)
{
    Vector2 mouse_pos = Input::mouse_position;
    Vector4 mous_pos_clip = Game::GetInstance()->camera2D->viewprojection_matrix * Vector4(mouse_pos.x,mouse_pos.y, 1.0, 1.0);
    
    if(Input::wasKeyPressed(SDL_SCANCODE_S))
    {
        Game::GetInstance()->GoToStage(PLAY_STAGE);
    }
    
    float left = play->pos_x - play->width/2;
    float right = play->pos_x + play->width/2;
    float top = play->pos_y - play->height/2;
    float bottom = play->pos_y + play->height/2;
    
    if(mous_pos_clip.x >= left && mous_pos_clip.x <= right && mous_pos_clip.y >= top && mous_pos_clip.y <= bottom){
        
        play->material.color = Vector4(1, 0, 0, 0);
        
        if(Input::isMousePressed(SDL_BUTTON_LEFT)){
            
            Game::GetInstance()->GoToStage(PLAY_STAGE);
        }

    }else{
        play->material.color = Vector4(1, 1, 1, 1);
    }
  
  
    
}

void IntroStage::onExit()
{
    Audio::Stop(channel_intro);
}

void IntroStage::onEnter()
{
    Audio::Init();
    channel_intro = Audio::Play("data/sounds/intro.wav", 1, BASS_SAMPLE_LOOP);
}




// PLAY STAGE


PlayStage::PlayStage()
{
    //loads

    //declarar variables com temps etc
}

void PlayStage::render()
{
    World::GetInstance()->render(Camera::current);
    //renderminimap();
    drawText(50, 50, std::to_string(money), Vector3(1, 0, 0), 5);

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

    if (int(Game::instance->time*10) % 5 == 0 && !moneyCounted) {
        if (numMines < 0) {
            numMines = 0;
        }
        money += 1 * numMines;
        moneyCounted = true;
    }
    if (int(Game::instance->time*10) % 5 == 1 && moneyCounted) {
        moneyCounted = false;
    }

   /* if (waveTimeOut <= 0 && nextWave) {
        std::getline(enemyWaves, waves);
        iter = 0;
        waveTimeOut = 2;
        nextWave = false;
    }
    else if(nextWave) {
        
        waveTimeOut -= seconds_elapsed;
    }*/
    if (World::GetInstance()->enemies.size() == 0) {
        std::getline(enemyWaves, waves);
        iter = 0;
        waveTimeOut = 2;
        nextWave = false;
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
                timeOut += 1.2;
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

    for (EntityEnemy* enemy : World::GetInstance()->enemies) {
        if (enemy->waypoint_index == World::GetInstance()->waypoints.size()) {
            enemy->Die();
            vides -= 1;
            HCHANNEL screams = Audio::Play("data/sounds/screams.wav");
        }
    }

    if (vides <= 0) {
        Game::GetInstance()->GoToStage(END_STAGE);
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
                if (money >= 8) {
                    money -= 8;
                    tower->ammo = 13;
                }
                else {
                    continue;
                }
            }
            else if(typeToPlace == BALLISTA) {
                if (money >= 3) {
                    money -= 3;
                    tower->ammo = 10;
                }
                else {
                    continue;
                }
            }
            else if (typeToPlace == CATAPULT) {
                if (money >= 5) {
                    money -= 5;
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
        HCHANNEL construction = Audio::Play("data/sounds/construction.wav");
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
    Audio::Stop(background_channel);
}

void PlayStage::onEnter()
{
    enemyWaves.open("data/EnemyWaves.txt", std::ios::in);
    background_channel = Audio::Play("data/sounds/play_background.wav", 1, BASS_SAMPLE_LOOP);
}

void PlayStage::renderminimap()
{
    
    Camera* curr = Camera::current;

    //clear depth buffer again to render UI
    glClear(GL_DEPTH_BUFFER_BIT);
    
    int width = Game::GetInstance()->window_width;
    int height = Game::GetInstance()->window_height;
    int size = 200;
    int margin = 40;
    glViewport(width - margin -size,  height - size-margin, size, size);
    


    Camera cam;
    cam.setPerspective(60, 1, 0.1, 100);
    Vector3 center(0, 0, 0);
    Vector3 eye = center + Vector3(0, 30, 0);
    Vector3 up(0, 0, -1);

    cam.lookAt(eye, center, up);
    cam.renderGUI = false;

    cam.enable();
    
    World::GetInstance()->root->render(&cam);

    
    curr->enable();

    //reset view
    glViewport(0, 0, width, height);



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

