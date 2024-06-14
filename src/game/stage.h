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
    virtual void onExit(int stage_to_go) {};
    
};

class IntroStage : public Stage
{ //per heredar
   
    
public:
    
    //Constructor
    IntroStage();
    
    SDL_Window* window;
    

    EntityUI* fons;
    EntityUI* play;
    EntityUI* exit;
    EntityUI* commands;
    Material material;
    
    Material play_m;
    Material exit_m;
    Material commands_m;
    
    float timer = 0;
    
    void render() override;
    void update(float seconse_elapsed) override;
    
    bool onButton(EntityUI* button);
    
    virtual void onEnter() override;
    virtual void onExit(int stage_to_go) override;



    
};

class SelectStage : public Stage {
public:

    SelectStage();


    EntityUI* fons;
    EntityUI* easy;
    EntityUI* puig;
    EntityUI* personalized;
    EntityUI* back;
    Material material;

    Material easy_m;
    Material puig_m;
    Material personalized_m;
    Material back_m;


    float timer = 0;


    void render() override;
    void update(float seconse_elapsed) override;

    bool onButton(EntityUI* button);

    virtual void onEnter() override;
    virtual void onExit(int stage_to_go) override;
};

class PersonalizeStage : public Stage{
public:
    PersonalizeStage();

    EntityUI* fons;
    EntityUI* normal;
    EntityUI* strong;
    EntityUI* fast;
    EntityUI* wave;
    EntityUI* play;
    EntityUI* back;
    Material material;

    Material normal_m;
    Material strong_m;
    Material fast_m;
    Material wave_m;
    Material play_m;
    Material back_m;


    EntityUI* normal_image;
    EntityUI* strong_image;
    EntityUI* fast_image;
    Material normal_i_m;
    Material strong_i_m;
    Material fast_i_m;

    int numNormal = 0;
    int numStrong = 0;
    int numFast = 0;

    std::ofstream personalized;


    float timer = 0;


    void render() override;
    void update(float seconse_elapsed) override;

    bool onButton(EntityUI* button);

    virtual void onEnter() override;
    virtual void onExit(int stage_to_go) override;
};

class CommandsStage : public Stage
{
    
public:
    // Constructor
    CommandsStage();
    EntityUI* menu;
    Material menu_m;
    
    HCHANNEL channel_intro;
    
    float timer = 0;

    
    void render() override;
    void update(float seconse_elapsed) override;
    
    bool onButton(EntityUI* button);
    
    virtual void onEnter() override;
    virtual void onExit(int stage_to_go) override;
    
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
    void SellTower();
    void renderminimap();
    
    virtual void onEnter() override;
    virtual void onExit(int stage_to_go) override;

    const char* towerType = "towerRound_sampleA.obj";
    int typeToPlace = MINE;

    bool moneyCounted = false;
    int money = 20;
    int numMines = 0;

    std::fstream enemyWaves;
    float waveTimeOut = 5;
    std::string waves = "a";
    bool nextWave = true;
    float timeOut = 0;
    int iter = 0;
    float waveTextTime = 0;
    
    
    int vides = 3;
    float vendreVidesTimeout = 0;

    bool minimap = true;

    bool stopLastGameEnemy = true;
    bool lastGameEnemyFound = false;

    HCHANNEL background_channel;

};

class LostStage : public Stage{
public:
    LostStage();

    EntityUI* fons;
    Material material;
    float color = 5;

    void render() override;
    void update(float seconds_elapsed) override;

    virtual void onEnter() override;
    virtual void onExit(int stage_to_go) override;
};

class WinStage : public Stage {
public:
    WinStage();

    EntityUI* fons;
    Material material;
    float color = 0;

    void render() override;
    void update(float seconds_elapsed) override;

    virtual void onEnter() override;
    virtual void onExit(int stage_to_go) override;
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
    virtual void onExit(int stage_to_go) override;
    
};

#endif 


