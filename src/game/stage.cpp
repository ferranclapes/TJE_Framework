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


void Stage::render()
{
   
    
}

void Stage::update(float seconse_elapsed)
{
    
}

// INTRO STAGE
IntroStage::IntroStage() {
    
   // FONS
    material.diffuse = Texture::Get("data/textures/intro.png");
    material.shader = Shader::Get("data/shaders/example.vs", "data/shaders/image.fs");
    fons = new EntityUI(0.0f, 0.0f, 2.0f, 2.0f, material);
    

    // BOTONS
   
    play_m.color = Vector4(1, 1, 1, 1);
    play = new EntityUI(0.0f, 0.0f, 0.5f, 0.2f, play_m);
    
    exit_m.color = Vector4(1, 1, 1, 1);
    exit = new EntityUI(0.0f, -0.3f, 0.5f, 0.2f, exit_m);
    
    commands_m.color = Vector4(1, 1, 1, 1);
    commands = new EntityUI(0.0f, -0.6f, 0.5f, 0.2f, exit_m);

    fons->addChild(play);
    play->addChild(exit);
    exit->addChild(commands);

}
    

void IntroStage::render()
{
    
    fons->render(Game::GetInstance()->camera2D);
    
    drawText(180, 140, "Guardians del castell", Vector3(0, 0, 0), 4);
    drawText(365, 290, "Start", Vector3(0, 0, 0), 3);
    drawText(370, 380, "Exit", Vector3(0, 0, 0), 3);
    drawText(330, 470, "Commands", Vector3(0, 0, 0), 3);
    
}

void IntroStage::update(float seconse_elapsed)
{

    if(Input::isMousePressed(SDL_SCANCODE_S))
    {
        Game::GetInstance()->GoToStage(PLAY_STAGE);
    }
  
    bool dins_play = onButton(play);
    bool dins_exit = onButton(exit);
    bool dins_commands = onButton(commands);
    
    if(dins_play){
        play->material.color = Vector4(1, 0, 0, 0);
        
        if(Input::isMousePressed(SDL_BUTTON_LEFT)){
            
            Game::GetInstance()->GoToStage(PLAY_STAGE);
        }
        
    }else if(dins_exit){
        exit->material.color = Vector4(1, 0, 0, 0);
        
        if(Input::isMousePressed(SDL_BUTTON_LEFT)){
            
            Game::GetInstance()->must_exit = true;
      
        }
        
    }else if(dins_commands){
        commands->material.color = Vector4(1, 0, 0, 0);
        
        if(Input::isMousePressed(SDL_BUTTON_LEFT)){
            
            Game::GetInstance()->GoToStage(COMMANDS_STAGE);
      
        }
        
    }else{
        play->material.color = Vector4(1, 1, 1, 1);
        exit->material.color = Vector4(1, 1, 1, 1);
        commands->material.color = Vector4(1, 1, 1, 1);
    }
  
  
    
}

bool IntroStage::onButton(EntityUI* button){
    
    Vector2 mouse_pos = Input::mouse_position;
    Vector4 mous_pos_clip = Game::GetInstance()->camera2D->viewprojection_matrix * Vector4(mouse_pos.x,mouse_pos.y, 1.0, 1.0);
    
    float left = button->pos_x - button->width/2;
    float right = button->pos_x + button->width/2;
    float top = button->pos_y - button->height/2;
    float bottom = button->pos_y + button->height/2;
    
    if(mous_pos_clip.x >= left && mous_pos_clip.x <= right && mous_pos_clip.y >= top && mous_pos_clip.y <= bottom){
        return true;
    }
    return false;
    
}

void IntroStage::onExit(int stage_to_go)
{
    if (stage_to_go != COMMANDS_STAGE) {

        Audio::Stop(channel_intro);
    }
}

void IntroStage::onEnter()
{
    if (channel_intro == NULL) {

        Audio::Init();
        channel_intro = Audio::Play("data/sounds/intro.wav", 1, BASS_SAMPLE_LOOP);
    }
}


//COMMANDS STAGE
CommandsStage::CommandsStage()
{

    menu_m.color = Vector4(1, 1, 1, 1);
    menu = new EntityUI(0.0f, 0.7f, 0.5f, 0.2f, menu_m);
}

void CommandsStage::render()
{
    menu->render(Game::GetInstance()->camera2D);
    
    drawText(365, 80, "Menu", Vector3(0, 0, 0), 3);
    drawText(150, 160, "A / D / w / S : Move camera", Vector3(1, 1, 1), 3);
    drawText(150, 220, "Z / X : Camera zomm", Vector3(1, 1, 1), 3);
    drawText(150, 300, "Click the base to place a tower", Vector3(1, 1, 1), 3);
    drawText(150, 340, "Towers:", Vector3(1, 1, 1), 3);
    drawText(180, 380, " - Mine : number 1", Vector3(1, 1, 1), 3);
    drawText(180, 420, " - Ballista : number 2", Vector3(1, 1, 1), 3);
    drawText(180, 460, " - Catapult : number 3", Vector3(1, 1, 1), 3);
    
}

void CommandsStage::update(float seconse_elapsed)
{
    bool dins_menu = onButton(menu);
    if(dins_menu){
        menu->material.color = Vector4(1, 0, 0, 0);
        
        if(Input::isMousePressed(SDL_BUTTON_LEFT)){
            
            Game::GetInstance()->GoToStage(INTRO_STAGE);
        }
        
    }else{
        menu->material.color = Vector4(1, 1, 1, 1);
        
    }

}
bool CommandsStage::onButton(EntityUI* button){
        
    Vector2 mouse_pos = Input::mouse_position;
    Vector4 mous_pos_clip = Game::GetInstance()->camera2D->viewprojection_matrix * Vector4(mouse_pos.x,mouse_pos.y, 1.0, 1.0);
    
    float left = button->pos_x - button->width/2;
    float right = button->pos_x + button->width/2;
    float top = button->pos_y - button->height/2;
    float bottom = button->pos_y + button->height/2;
        
    if(mous_pos_clip.x >= left && mous_pos_clip.x <= right && mous_pos_clip.y >= top && mous_pos_clip.y <= bottom){
        return true;
    }
    return false;
    
}
    
void CommandsStage::onExit(int stage_to_go)
{

}

void CommandsStage::onEnter()
{

}



// PLAY STAGE


PlayStage::PlayStage()
{
    //Estat jugador
    estat_m.diffuse = Texture::Get("data/textures/estat.png");
    estat_m.shader = Shader::Get("data/shaders/example.vs", "data/shaders/image.fs");
    estat = new EntityUI(-0.6f, -0.8f, 0.5f, 0.15f, estat_m);
    
    //Info torrew
    info_m.diffuse = Texture::Get("data/textures/info.png");
    info_m.shader = Shader::Get("data/shaders/example.vs", "data/shaders/image.fs");
    info = new EntityUI(-0.75f, 0.8f, 0.4f, 0.3f, info_m);
    
    estat->addChild(info);

}

void PlayStage::render()
{
    
    World::GetInstance()->render(Camera::current);
    estat->render(Game::GetInstance()->camera2D);

    renderminimap();
    
    drawText(210, 530, std::to_string(money), Vector3(1, 1, 1), 3);
    drawText(110, 530, std::to_string(vides), Vector3(1, 1, 1), 3);
    

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
            else if (waves[iter] == 'E'){
                Game::GetInstance()->GoToStage(WIN_STAGE);
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
        Game::GetInstance()->GoToStage(LOST_STAGE);
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

void PlayStage::onExit(int stage_to_go)
{
    Audio::Stop(background_channel);
}

void PlayStage::onEnter()
{
    enemyWaves.open("data/EnemyWaves.txt", std::ios::in);
    background_channel = Audio::Play("data/sounds/play_background.wav", 1, BASS_SAMPLE_LOOP);
    vides = 3;
    money = 20;
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


//LOST STAGE

LostStage::LostStage() {
    // FONS
    material.color = Vector4(color, 0, 0, 1);
    material.shader = Shader::Get("data/shaders/example.vs", "data/shaders/flat.fs");
    fons = new EntityUI(0.0f, 0.0f, 2.0f, 2.0f, material);
}

void LostStage::render() {
    fons->render(Game::GetInstance()->camera2D);
    drawText(240, 260, "YOU LOST", Vector3(0, 0, 0), 7);
}

void LostStage::update(float seconds_elapsed) {
    color = (color - seconds_elapsed);
    material.color = Vector4(color/5, 0, 0, 1);
    fons->material = material;
    if (color <= -0) {
        Game::GetInstance()->GoToStage(END_STAGE);
    }
}

void LostStage::onEnter() {
    color = 5;
}

void LostStage::onExit(int stage_to_go) {

}


//WIN STAGE

WinStage::WinStage() {
    // FONS
    material.color = Vector4(color, 0, 0, 1);
    material.shader = Shader::Get("data/shaders/example.vs", "data/shaders/flat.fs");
    fons = new EntityUI(0.0f, 0.0f, 2.0f, 2.0f, material);
}

void WinStage::render() {
    fons->render(Game::GetInstance()->camera2D);
    drawText(240, 260, "YOU WIN", Vector3(0, 0, 0), 7);
}

void WinStage::update(float seconds_elapsed) {
    color = (color + seconds_elapsed);
    material.color = Vector4(0, color / 5, 0, 1);
    fons->material = material;
    if (color >= 5) {
        Game::GetInstance()->GoToStage(END_STAGE);
    }
}

void WinStage::onEnter() {
    color = 0;
}

void WinStage::onExit(int stage_to_go) {

}


// END STAGE
    
EndStage::EndStage()
{
    // FONS
     material.diffuse = Texture::Get("data/textures/intro.png");
     material.shader = Shader::Get("data/shaders/example.vs", "data/shaders/image.fs");
     fons = new EntityUI(0.0f, 0.0f, 2.0f, 2.0f, material);
    
    init_menu_m.color = Vector4(1, 1, 1, 1);
    init_menu = new EntityUI(0.0f, 0.3f, 0.5f, 0.2f, init_menu_m);
    
    restart_m.color = Vector4(1, 1, 1, 1);
    restart = new EntityUI(0.0f, 0.0f, 0.5f, 0.2f, restart_m);
    
    exit_m.color = Vector4(1, 1, 1, 1);
    exit = new EntityUI(0.0f, -0.3f, 0.5f, 0.2f, exit_m);
    
    fons->addChild(init_menu);
    init_menu->addChild(restart);
    restart->addChild(exit);
       
}

void EndStage::render()
{
    fons->render(Game::GetInstance()->camera2D);
    drawText(370, 200, "Menu", Vector3(0, 0, 0), 3);
    drawText(350, 290, "Restart", Vector3(0, 0, 0), 3);
    drawText(370, 380, "Exit", Vector3(0, 0, 0), 3);
    
}

void EndStage::update(float seconse_elapsed)
{
    bool dins_restart = onButton(restart);
    bool dins_exit = onButton(exit);
    bool dins_menu = onButton(init_menu);
    
    if(dins_restart){
        restart->material.color = Vector4(1, 0, 0, 0);
        
        if(Input::isMousePressed(SDL_BUTTON_LEFT)){
            
            Game::GetInstance()->GoToStage(PLAY_STAGE);
        }
        
    }else if(dins_exit){
        
        exit->material.color = Vector4(1, 0, 0, 0);
        
        if(Input::isMousePressed(SDL_BUTTON_LEFT)){
    
            Game::GetInstance()->must_exit = true;
      
        }
        
    }else if(dins_menu){
        init_menu->material.color = Vector4(1, 0, 0, 0);
        
        if(Input::isMousePressed(SDL_BUTTON_LEFT)){
            
            Game::GetInstance()->GoToStage(INTRO_STAGE);
        }
    }else{
        restart->material.color = Vector4(1, 1, 1, 1);
        exit->material.color = Vector4(1, 1, 1, 1);
        init_menu->material.color = Vector4(1, 1, 1, 1);
        
    }

}

void EndStage::onExit(int stage_to_go)
{
    Audio::Stop(channel_intro);
}

void EndStage::onEnter()
{
    Audio::Init();
    channel_intro = Audio::Play("data/sounds/intro.wav", 1, BASS_SAMPLE_LOOP);
}

bool EndStage::onButton(EntityUI* button){
        
    Vector2 mouse_pos = Input::mouse_position;
    Vector4 mous_pos_clip = Game::GetInstance()->camera2D->viewprojection_matrix * Vector4(mouse_pos.x,mouse_pos.y, 1.0, 1.0);
    
    float left = button->pos_x - button->width/2;
    float right = button->pos_x + button->width/2;
    float top = button->pos_y - button->height/2;
    float bottom = button->pos_y + button->height/2;
        
    if(mous_pos_clip.x >= left && mous_pos_clip.x <= right && mous_pos_clip.y >= top && mous_pos_clip.y <= bottom){
        return true;
    }
    return false;
    
}
