/*  by Javi Agenjo 2013 UPF  javi.agenjo@gmail.com
	This class encapsulates the game, is in charge of creating the game, getting the user input, process the update and render.
*/

#pragma once
class Entity;
class Matrix44;
class Material;
class EntityMesh;
class Mesh;
class Camera;

class World
{
public:
    static World* instance;

    World();
   
    // Entity root;
    int window_width;
    int window_height;

    Entity* root;
    
    void render(Camera* camera);
    void update();
    
    bool parseScene(const char* filename, Entity* root);
    
    
};

