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

HCHANNEL channel_intro = NULL;

int level;

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
    drawText(340, 470, "Controls", Vector3(0, 0, 0), 3);
    
}

void IntroStage::update(float seconse_elapsed)
{
  
    bool dins_play = onButton(play);
    bool dins_exit = onButton(exit);
    bool dins_commands = onButton(commands);
    
    if (timer >= 0.5){
        if (dins_play) {
            play->material.color = Vector4(1, 0, 0, 0);

            if (Input::isMousePressed(SDL_BUTTON_LEFT)) {

                Audio::Play("data/sounds/menu.wav", 1, BASS_SAMPLE_MONO);
                Game::GetInstance()->GoToStage(SELECT_STAGE);
            }

        }
        else if (dins_exit) {
            exit->material.color = Vector4(1, 0, 0, 0);

            if (Input::isMousePressed(SDL_BUTTON_LEFT)) {

                Audio::Play("data/sounds/menu.wav", 2, BASS_SAMPLE_MONO);
                Game::GetInstance()->must_exit = true;

            }

        }
        else if (dins_commands) {
            commands->material.color = Vector4(1, 0, 0, 0);

            if (Input::isMousePressed(SDL_BUTTON_LEFT)) {

                Audio::Play("data/sounds/menu.wav", 2, BASS_SAMPLE_MONO);
                Game::GetInstance()->GoToStage(COMMANDS_STAGE);

            }

        }
        else {
            play->material.color = Vector4(1, 1, 1, 1);
            exit->material.color = Vector4(1, 1, 1, 1);
            commands->material.color = Vector4(1, 1, 1, 1);
        }
    }
  
    timer += seconse_elapsed;
    
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
    
}

void IntroStage::onEnter()
{
    timer = 0;
    play->material.color = Vector4(1, 1, 1, 1);
    exit->material.color = Vector4(1, 1, 1, 1);
    commands->material.color = Vector4(1, 1, 1, 1);
    if (channel_intro == NULL) {

        //Audio::Init();
        channel_intro = Audio::Play("data/sounds/intro.wav", 0.7, BASS_SAMPLE_LOOP);
    }
}



//SELECT STAGE

SelectStage::SelectStage() {
    // FONS
    material.diffuse = Texture::Get("data/textures/intro.png");
    material.shader = Shader::Get("data/shaders/example.vs", "data/shaders/image.fs");
    fons = new EntityUI(0.0f, 0.0f, 2.0f, 2.0f, material);


    // BOTONS
    easy_m.color = Vector4(1, 1, 1, 1);
    easy = new EntityUI(0.0f, 0.3f, 0.5f, 0.2f, easy_m);

    puig_m.color = Vector4(1, 1, 1, 1);
    puig = new EntityUI(0.0f, 0.0f, 0.65f, 0.2f, puig_m);

    personalized_m.color = Vector4(1, 1, 1, 1);
    personalized = new EntityUI(0.0f, -0.3f, 0.65f, 0.2f, personalized_m);

    back_m.color = Vector4(1, 1, 1, 1);
    back = new EntityUI(0.0f, -0.6f, 0.5f, 0.2f, back_m);

    fons->addChild(easy);
    easy->addChild(puig);
    puig->addChild(personalized);
    personalized->addChild(back);
}

void SelectStage::render()
{

    fons->render(Game::GetInstance()->camera2D);

    drawText(180, 110, "Select level difficulty", Vector3(0, 0, 0), 4);
    drawText(355, 200, "Normal", Vector3(0, 0, 0), 3);
    drawText(295, 290, "Puig Challenge", Vector3(0, 0, 0), 3);
    drawText(310, 380, "Personalized", Vector3(0, 0, 0), 3);
    drawText(368, 470, "Back", Vector3(0, 0, 0), 3);
}

void SelectStage::update(float seconse_elapsed)
{

    bool dins_easy = onButton(easy);
    bool dins_puig = onButton(puig);
    bool dins_personalized = onButton(personalized);
    bool dins_back = onButton(back);

    if (timer >= 0.5){
        if (dins_easy) {
            easy->material.color = Vector4(1, 0, 0, 0);

            if (Input::isMousePressed(SDL_BUTTON_LEFT)) {

                Audio::Play("data/sounds/menu.wav", 1, BASS_SAMPLE_MONO);
                level = 0;
                Game::GetInstance()->GoToStage(PLAY_STAGE);
            }

        }
        else if (dins_puig) {
            puig->material.color = Vector4(1, 0, 0, 0);

            if (Input::isMousePressed(SDL_BUTTON_LEFT)) {

                level = 1;
                Audio::Play("data/sounds/menu.wav", 2, BASS_SAMPLE_MONO);
                Game::GetInstance()->GoToStage(PLAY_STAGE);

            }

        }
        else if (dins_personalized) {
            personalized->material.color = Vector4(1, 0, 0, 0);

            if (Input::isMousePressed(SDL_BUTTON_LEFT)) {

                Audio::Play("data/sounds/menu.wav", 2, BASS_SAMPLE_MONO);
                Game::GetInstance()->GoToStage(PERSONALIZED_STAGE);

            }
        }
        else if (dins_back) {
            back->material.color = Vector4(1, 0, 0, 0);

            if (Input::isMousePressed(SDL_BUTTON_LEFT)) {

                Audio::Play("data/sounds/menu.wav", 2, BASS_SAMPLE_MONO);
                Game::GetInstance()->GoToStage(INTRO_STAGE);

            }

        }
        else {
            easy->material.color = Vector4(1, 1, 1, 1);
            puig->material.color = Vector4(1, 1, 1, 1);
            personalized->material.color = Vector4(1, 1, 1, 1);
            back->material.color = Vector4(1, 1, 1, 1);
        }
    }

    timer += seconse_elapsed;



}

bool SelectStage::onButton(EntityUI* button) {

    Vector2 mouse_pos = Input::mouse_position;
    Vector4 mous_pos_clip = Game::GetInstance()->camera2D->viewprojection_matrix * Vector4(mouse_pos.x, mouse_pos.y, 1.0, 1.0);

    float left = button->pos_x - button->width / 2;
    float right = button->pos_x + button->width / 2;
    float top = button->pos_y - button->height / 2;
    float bottom = button->pos_y + button->height / 2;

    if (mous_pos_clip.x >= left && mous_pos_clip.x <= right && mous_pos_clip.y >= top && mous_pos_clip.y <= bottom) {
        return true;
    }
    return false;

}

void SelectStage::onExit(int stage_to_go)
{
    if (stage_to_go == PLAY_STAGE) {
        Audio::Stop(channel_intro);
    }
}

void SelectStage::onEnter()
{
    timer = 0;
    easy->material.color = Vector4(1, 1, 1, 1);
    puig->material.color = Vector4(1, 1, 1, 1);
    back->material.color = Vector4(1, 1, 1, 1);
}


//PERSONALIZE STAGE
PersonalizeStage::PersonalizeStage() {
    // FONS
    material.diffuse = Texture::Get("data/textures/intro.png");
    material.shader = Shader::Get("data/shaders/example.vs", "data/shaders/image.fs");
    fons = new EntityUI(0.0f, 0.0f, 2.0f, 2.0f, material);


    // BOTONS
    normal_m.color = Vector4(1, 1, 1, 1);
    normal = new EntityUI(-0.6f, 0.0f, 0.5f, 0.7f, normal_m);

    strong_m.color = Vector4(1, 1, 1, 1);
    strong = new EntityUI(0.0f, -0.0f, 0.5f, 0.7f, strong_m);

    fast_m.color = Vector4(1, 1, 1, 1);
    fast = new EntityUI(0.6f, -0.0f, 0.5f, 0.7f, fast_m);

    wave_m.color = Vector4(1, 1, 1, 1);
    wave = new EntityUI(-0.35f, -0.6f, 0.5f, 0.2f, wave_m);

    play_m.color = Vector4(1, 1, 1, 1);
    play = new EntityUI(0.35f, -0.6f, 0.5f, 0.2f, play_m);

    back_m.color = Vector4(1, 1, 1, 1);
    back = new EntityUI(0.0f, -0.85f, 0.5f, 0.2f, back_m);

    //IMATGES
    normal_i_m.diffuse = Texture::Get("data/textures/normal.png");
    normal_i_m.shader = Shader::Get("data/shaders/example.vs", "data/shaders/image.fs");
    normal_image = new EntityUI(-0.6f, 0.0f, 0.5f, 0.2f, normal_i_m);

    strong_i_m.diffuse = Texture::Get("data/textures/strong.png");
    strong_i_m.shader = Shader::Get("data/shaders/example.vs", "data/shaders/image.fs");
    strong_image = new EntityUI(0.0f, -0.0f, 0.5f, 0.7f, strong_i_m);

    fast_i_m.diffuse = Texture::Get("data/textures/fast.png");
    fast_i_m.shader = Shader::Get("data/shaders/example.vs", "data/shaders/image.fs");
    fast_image = new EntityUI(0.6f, -0.0f, 0.5f, 0.7f, fast_i_m);

    fons->addChild(normal);
    normal->addChild(strong);
    strong->addChild(fast);
    fast->addChild(wave);
    wave->addChild(play);
    wave->addChild(back);
    //normal->addChild(normal_image);
    //strong->addChild(strong_image);
    //fast->addChild(fast_image);
}

void PersonalizeStage::render() {
    fons->render(Game::GetInstance()->camera2D);

    drawText(160, 100, "Create your own game!", Vector3(0, 0, 0), 4);
    drawText(180, 470, "Next Wave", Vector3(0, 0, 0), 3);
    drawText(510, 470, "Play", Vector3(0, 0, 0), 3);
    drawText(90, 375, "Normal: " + std::to_string(numNormal), Vector3(0, 0, 0), 3);
    drawText(320, 375, "Strong: " + std::to_string(numStrong), Vector3(0, 0, 0), 3);
    drawText(570, 375, "Fast: " + std::to_string(numFast), Vector3(0, 0, 0), 3);
    drawText(365, 545, "Back", Vector3(0, 0, 0), 3);
}

void PersonalizeStage::update(float seconds_elapsed) {
    bool dins_normal = onButton(normal);
    bool dins_strong = onButton(strong);
    bool dins_fast = onButton(fast);
    bool dins_wave = onButton(wave);
    bool dins_play = onButton(play);
    bool dins_back = onButton(back);

    if (timer >= 0.1) {
        if (dins_normal) {
            normal->material.color = Vector4(1, 0, 0, 0);

            if (Input::isMousePressed(SDL_BUTTON_LEFT)) {
                timer = 0;
                Audio::Play("data/sounds/menu.wav", 1, BASS_SAMPLE_MONO);
                numNormal += 1;
                personalized << "N";
            }

        }
        else if (dins_strong) {
            strong->material.color = Vector4(1, 0, 0, 0);

            if (Input::isMousePressed(SDL_BUTTON_LEFT)) {
                timer = 0;
                Audio::Play("data/sounds/menu.wav", 2, BASS_SAMPLE_MONO);
                numStrong++;
                personalized << "S";

            }

        }
        else if (dins_fast) {
            fast->material.color = Vector4(1, 0, 0, 0);

            if (Input::isMousePressed(SDL_BUTTON_LEFT)) {
                timer = 0;
                Audio::Play("data/sounds/menu.wav", 2, BASS_SAMPLE_MONO);
                numFast++;
                personalized << "F";
            }

        }
        else if (dins_wave) {
            wave->material.color = Vector4(1, 0, 0, 0);
            if (Input::isMousePressed(SDL_BUTTON_LEFT)) {
                timer = 0;
                numNormal = 0;
                numStrong = 0;
                numFast = 0;
                personalized << "\n";
            }
        }
        else if (dins_play) {
            play->material.color = Vector4(1, 0, 0, 0);

            if (Input::isMousePressed(SDL_BUTTON_LEFT)) {

                level = 2;
                Audio::Play("data/sounds/menu.wav", 2, BASS_SAMPLE_MONO);
                Game::GetInstance()->GoToStage(PLAY_STAGE);

            }
        }
        else if (dins_back) {
            back->material.color = Vector4(1, 0, 0, 0);
            if (Input::isMousePressed(SDL_BUTTON_LEFT)) {

                Audio::Play("data/sounds/menu.wav", 2, BASS_SAMPLE_MONO);
                Game::GetInstance()->GoToStage(SELECT_STAGE);

            }
        }
        else {
            normal->material.color = Vector4(1, 1, 1, 1);
            strong->material.color = Vector4(1, 1, 1, 1);
            fast->material.color = Vector4(1, 1, 1, 1);
            wave->material.color = Vector4(1, 1, 1, 1);
            play->material.color = Vector4(1, 1, 1, 1);
            back->material.color = Vector4(1, 1, 1, 1);
        }
    }

    timer += seconds_elapsed;



}

bool PersonalizeStage::onButton(EntityUI* button) {

    Vector2 mouse_pos = Input::mouse_position;
    Vector4 mous_pos_clip = Game::GetInstance()->camera2D->viewprojection_matrix * Vector4(mouse_pos.x, mouse_pos.y, 1.0, 1.0);

    float left = button->pos_x - button->width / 2;
    float right = button->pos_x + button->width / 2;
    float top = button->pos_y - button->height / 2;
    float bottom = button->pos_y + button->height / 2;

    if (mous_pos_clip.x >= left && mous_pos_clip.x <= right && mous_pos_clip.y >= top && mous_pos_clip.y <= bottom) {
        return true;
    }
    return false;

}

void PersonalizeStage::onExit(int stage_to_go) {
    if (stage_to_go == PLAY_STAGE) {
        Audio::Stop(channel_intro);
    }
    personalized << "\nE";
    personalized.close();
}

void PersonalizeStage::onEnter() {
    personalized.open("data/PersonalizedWaves.txt");
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
    drawText(100, 150, "A / D / w / S : Move camera", Vector3(1, 1, 1), 3);
    drawText(100, 190, "Z / X : Camera zomm", Vector3(1, 1, 1), 3);
    drawText(100, 230, "Click the the number of the desired ", Vector3(1, 1, 1), 3);
    drawText(100, 270, "tower type and a base to place a tower.", Vector3(1, 1, 1), 3);
    drawText(100, 310, "Mine towers only get money if there", Vector3(1, 1, 1), 3);
    drawText(100, 350, "are diamonds nearby.", Vector3(1, 1, 1), 3);
    drawText(100, 390, "Towers types:", Vector3(1, 1, 1), 3);
    drawText(120, 430, " - Mine : number 1", Vector3(1, 1, 1), 3);
    drawText(120, 470, " - Ballista : number 2", Vector3(1, 1, 1), 3);
    drawText(120, 510, " - Catapult : number 3", Vector3(1, 1, 1), 3);
    drawText(100, 560, "Activate/Deactivate minimap with M", Vector3(1, 1, 1), 3);
    
    
}

void CommandsStage::update(float seconse_elapsed)
{
    bool dins_menu = onButton(menu);
    if(dins_menu){
        menu->material.color = Vector4(1, 0, 0, 0);
        
        if(Input::isMousePressed(SDL_BUTTON_LEFT)){

            Audio::Play("data/sounds/menu.wav", 2, BASS_SAMPLE_MONO);
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

    if (minimap){
        renderminimap();
    }

    drawText(210, 530, std::to_string(money), Vector3(1, 1, 1), 3);
    drawText(110, 530, std::to_string(vides), Vector3(1, 1, 1), 3);
    if (waveTextTime >= 1.5 || (waveTextTime >=0.5 && waveTextTime <= 1.0)) {
        drawText(150, 260, "ENEMIES INCOMING", Vector3(0.7, 0, 0), 6);
    }
    

}

void PlayStage::update(float seconds_elapsed)
{
    if (Input::wasKeyPressed(SDL_SCANCODE_L)) {
        vides--;
    }


    if (Input::wasKeyPressed(SDL_SCANCODE_M)) {
        if (minimap) {
            minimap = false;
        }
        else {
            minimap = true;
        }
    }
    if(Input::isMousePressed(SDL_BUTTON_LEFT))
    {
        PlaceTower();
    }
    if (Input::isMousePressed(SDL_BUTTON_RIGHT)) {
        SellTower();
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

    if (int(Game::instance->time*10) % 10 == 0 && !moneyCounted) {
        if (numMines < 0) {
            numMines = 0;
        }
        money += 1 * numMines;
        moneyCounted = true;
    }
    if (int(Game::instance->time*10) % 10 == 1 && moneyCounted) {
        moneyCounted = false;
    }

   
    if (World::GetInstance()->enemies.size() == 0) {
        if (waveTimeOut <= 0 && nextWave) {
            std::getline(enemyWaves, waves);
            iter = 0;
            waveTimeOut = 5;
            nextWave = false;
            waveTextTime = 2;
        }
        else if (nextWave) {

            waveTimeOut -= seconds_elapsed;
        }
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

    if (waveTextTime >= 0) {
        waveTextTime -= seconds_elapsed;
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

    vendreVidesTimeout -= seconds_elapsed;


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

            if (collider->coliderType == CITY && vendreVidesTimeout <= 0) {
                if (vides > 1) {
                    vides -= 1;
                    money += 30;
                    Audio::Play("data/sounds/money.wav", 1, BASS_SAMPLE_MONO);
                    vendreVidesTimeout = 1;
                }
                else {
                    Audio::Play("data/sounds/wrong.wav", 1, BASS_SAMPLE_MONO);
                }
            }

            EntityTower* tower = dynamic_cast<EntityTower*>(collider);

            if (!tower || tower->towerType != EMPTY) {
                continue;
            }


            if (typeToPlace == MINE) {
                if (money >= 8) {
                    money -= 7;
                    tower->ammo = 13;
                }
                else {
                    Audio::Play("data/sounds/wrong.wav", 1, BASS_SAMPLE_MONO);
                    continue;
                }
            }
            else if(typeToPlace == BALLISTA) {
                if (money >= 3) {
                    money -= 3;
                    tower->ammo = 15;
                    tower->cooldown = 0.7;
                }
                else {
                    Audio::Play("data/sounds/wrong.wav", 1, BASS_SAMPLE_MONO);
                    continue;
                }
            }
            else if (typeToPlace == CATAPULT) {
                if (money >= 5) {
                    money -= 5;
                    tower->ammo = 4;
                    tower->cooldown = 2;
                }
                else {
                    Audio::Play("data/sounds/wrong.wav", 1, BASS_SAMPLE_MONO);
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

void PlayStage::SellTower() {
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

            if (!tower || tower->towerType == EMPTY) {
                continue;
            }
            if (tower->towerType == MINE) {
                Audio::Play("data/sounds/wrong.wav", 1, BASS_SAMPLE_MONO);
                continue;
            }

            if (tower->towerType == BALLISTA) {
                money += 2;
            }
            else if (tower->towerType == CATAPULT) {
                money += 3;
            }
            Audio::Play("data/sounds/money.wav", 1, BASS_SAMPLE_MONO);
            tower->EliminateTower();
        }
    }

}

void PlayStage::onExit(int stage_to_go)
{
    enemyWaves.close();
    Audio::Stop(background_channel);
}

void PlayStage::onEnter()
{

    float waveTimeOut = 5;
    std::string waves = "a";
    bool nextWave = true;
    float timeOut = 0;
    int iter = 0;
    float waveTextTime = 0;
    if (level == 0) {
        enemyWaves.open("data/EnemyWaves.txt", std::ios::in);
    }
    else if (level == 1) {
        enemyWaves.open("data/PuigChallenge.txt", std::ios::in);
    }
    else if (level == 2) {
        enemyWaves.open("data/PersonalizedWaves.txt", std::ios::in);
    }
    background_channel = Audio::Play("data/sounds/play_background.wav", 1, BASS_SAMPLE_LOOP);
    vides = 3;
    money = 20;


    int index = World::GetInstance()->enemies.size();
    for (int i = 0; i < index; i++) {
        int j = World::GetInstance()->enemies.size() - 1;
        EntityEnemy* enemy = World::GetInstance()->enemies[j];
        enemy->Die();
    }


    for (Entity* e : World::GetInstance()->root->children) {
        EntityTower* tower = dynamic_cast<EntityTower*>(e);
        if (!tower) {
            continue;
        }
        if (tower->towerType != EMPTY) {
            tower->EliminateTower();
        }
    }
}

void PlayStage::renderminimap()
{
    
    Camera* curr = Camera::current;

    //clear depth buffer again to render UI
    glClear(GL_DEPTH_BUFFER_BIT);
    
    int width = Game::GetInstance()->window_width;
    int height = Game::GetInstance()->window_height;
    int size = 150;
    int margin = 20;
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

    Audio::Play("data/sounds/lost.wav", 2, BASS_SAMPLE_MONO);
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
    Audio::Play("data/sounds/win.wav", 2, BASS_SAMPLE_MONO);
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
    if (stage_to_go != INTRO_STAGE) {
        Audio::Stop(channel_intro);
    }
}

void EndStage::onEnter()
{
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
