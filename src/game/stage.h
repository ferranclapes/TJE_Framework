//
//  stage.hpp
//  TJE_Framework
//
//  Created by Alba Arcos on 27/4/24.
//

/*#ifndef stage_hpp
#define stage_hpp

#include <stdio.h>




class Stage{
    
public:
   
    virtual void render(Image* framebuffer, float seconse_elapsed);
    virtual void update(float seconse_elapsed);
    
    virtual void onEnter() {};
    virtual void onExit() {};
    
};

class IntroStage : public Stage
{ //per heredar
   
    
public:
    
    //Constructor
    IntroStage();
    
    void render(Image* framebuffer, float seconse_elapsed) override;
    void update(float seconse_elapsed) override;
    
    virtual void onEnter() override;
    virtual void onExit() override;
};


class PlayStage : public Stage
{ //per heredar

public:
    
    //Constructor
    PlayStage();
    
    void render(Image* framebuffer, float seconse_elapsed) override;
    void update(float seconds_elapsed) override;
    
    virtual void onEnter() override;
    virtual void onExit() override;
   

};

class EndStage : public Stage
{
    
public:
    // Constructor
    EndStage();
    
    void render(Image* framebuffer, float seconse_elapsed) override;
    void update(float seconse_elapsed) override;
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
};

#endif /* stage_hpp */

