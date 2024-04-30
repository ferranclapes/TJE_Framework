/*  by Javi Agenjo 2013 UPF  javi.agenjo@gmail.com
	This class encapsulates the game, is in charge of creating the game, getting the user input, process the update and render.
*/

#pragma once


class World
{
public:
    
   
    // Entity* root;
    int window_width;
    int window_height;
    
    
    void render();
    void update();
    
    
}
