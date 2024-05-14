//
//  stage.hpp
//  TJE_Framework
//
//  Created by Alba Arcos on 27/4/24.
//

#ifndef stage_hpp
#define stage_hpp

#include <stdio.h>


#include "framework/camera.h"

class Stage{
    
public:
   
    virtual void render(float seconse_elapsed);
    virtual void update(float seconse_elapsed);
    
    virtual void onEnter() {};
    virtual void onExit() {};
    
};

class IntroStage : public Stage
{ //per heredar
   
    
public:
    
    //Constructor
    IntroStage();
    
    void render(float seconse_elapsed) override;
    void update(float seconse_elapsed) override;
    
    virtual void onEnter() override;
    virtual void onExit() override;
};


class PlayStage : public Stage
{ //per heredar

public:
    
    //Constructor
    PlayStage();
    
    void render(float seconse_elapsed) override;
    void update(float seconds_elapsed) override;
    
    virtual void onEnter() override;
    virtual void onExit() override;
   

};

class EndStage : public Stage
{
    
public:
    // Constructor
    EndStage();
    
    void render(float seconse_elapsed) override;
    void update(float seconse_elapsed) override;
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
};

#endif 


