/*  by Javi Agenjo 2013 UPF  javi.agenjo@gmail.com
	This class encapsulates the game, is in charge of creating the game, getting the user input, process the update and render.
*/


#pragma once
#include <vector>

class Entity;
class Matrix44;
class Material;
class EntityMesh;
class Mesh;
class Camera;
class EntityEnemy;
class EntityTower;

class World
{
    static World* instance;
public:
    

    World();
   
    // Entity root;
    int window_width;
    int window_height;

    Entity* root;

    std::vector<EntityTower*> towers;

    std::vector<EntityEnemy*> enemies;
    void RemoveEnemy(EntityEnemy* enemy);
    
    void render(Camera* camera);
    void update();
    
    bool parseScene(const char* filename, Entity* root);

    static World* GetInstance();
    void addEntity(Entity* new_entity);
    void removeEntity(Entity* e);
    
    
};

