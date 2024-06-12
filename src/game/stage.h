//
//  stage.hpp
//  TJE_Framework
//
//  Created by Alba Arcos on 27/4/24.
//

#ifndef stage_hpp
#define stage_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>


#include "framework/camera.h"
#include "graphics/mesh.h"
#include "graphics/texture.h"
#include "graphics/shader.h"
#include "framework/utils.h"
#include "framework/audio.h"
#include "graphics/material.h"



class EntityEnemy;
class EntityUI;
class Material;

enum TowerType {
    EMPTY,
    MINE,
    BALLISTA,
    CATAPULT
};

class Stage{
    
public:
   
    virtual void render();
    virtual void update(float seconse_elapsed);
    
    virtual void onEnter() {};
    virtual void onExit() {};
    
};

class IntroStage : public Stage
{ //per heredar
   
    
public:
    
    //Constructor
    IntroStage();
    
    SDL_Window* window;
    
    /*Mesh* mesh;
    //Shader* shader;
    Camera* camera;
    Texture* texture;*/
   
   // Mesh* fons;
    EntityUI* fons;
    EntityUI* play;
    EntityUI* exit;
    EntityUI* commands;
    Material material;
    
    Material fons_m;
    Material play_m;
    Material exit_m;
    Material commands_m;
    

    
    void render() override;
    void update(float seconse_elapsed) override;
    
    bool onButton(EntityUI* button);
    
    virtual void onEnter() override;
    virtual void onExit() override;



    HCHANNEL channel_intro;
};

class CommandsStage : public Stage
{
    
public:
    // Constructor
    CommandsStage();
    EntityUI* menu;
    Material menu_m;
    
    HCHANNEL channel_intro;
    
    void render() override;
    void update(float seconse_elapsed) override;
    
    bool onButton(EntityUI* button);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
};


class PlayStage : public Stage
{ //per heredar

public:
    
    //Constructor
    PlayStage();
    
    EntityUI* estat;
    Material estat_m;
    
    EntityUI* info;
    Material info_m;
    
    void render() override;
    void update(float seconds_elapsed) override;

    void PlaceTower();
    void renderminimap();
    
    virtual void onEnter() override;
    virtual void onExit() override;

    const char* towerType = "towerRound_sampleA.obj";
    int typeToPlace = MINE;

    bool moneyCounted = false;
    int money = 20;
    int numMines = 0;

    std::fstream enemyWaves;
    float waveTimeOut = 10;
    std::string waves = "a";
    bool nextWave = true;
    float timeOut = 0;
    int iter = 0;
    int vides = 3;


    HCHANNEL background_channel;

};

class EndStage : public Stage
{
    
public:
    // Constructor
    EndStage();
    
    EntityUI* fons;
    Material material;
    
    EntityUI* init_menu;
    Material init_menu_m;
    
    EntityUI* restart;
    Material restart_m;
    
    EntityUI* exit;
    Material exit_m;
    
    HCHANNEL channel_intro;
    
    void render() override;
    void update(float seconse_elapsed) override;
    
    bool onButton(EntityUI* button);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
};

#endif 


