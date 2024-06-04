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

class EntityEnemy;


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
    
    void render() override;
    void update(float seconse_elapsed) override;
    
    virtual void onEnter() override;
    virtual void onExit() override;
};

class PlayStage : public Stage
{ //per heredar

public:
    
    //Constructor
    PlayStage();
    
    void render() override;
    void update(float seconds_elapsed) override;

    void PlaceTower();
    
    virtual void onEnter() override;
    virtual void onExit() override;

    const char* towerType = "towerRound_sampleA.obj";
    int typeToPlace = MINE;

    bool moneyCounted = false;
    int money = 20;
    int numMines = 0;

    std::fstream enemyWaves;
    float waveTimeOut = 2;
    std::string waves = "a";
    bool nextWave = true;
    float timeOut = 0;
    int iter = 0;


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


