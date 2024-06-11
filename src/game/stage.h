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
   
    EntityUI* fons;
    EntityUI* play;

    
    void render() override;
    void update(float seconse_elapsed) override;
    
    virtual void onEnter() override;
    virtual void onExit() override;



    HCHANNEL channel_intro;
};

class PlayStage : public Stage
{ //per heredar

public:
    
    //Constructor
    PlayStage();
    
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
    float waveTimeOut = 1;
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
    
    void render() override;
    void update(float seconse_elapsed) override;
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
};

#endif 


