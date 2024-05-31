#include "entityEnemy.h"
#include "entityMesh.h"
#include "framework/camera.h"
#include "graphics/mesh.h"
#include "graphics/shader.h"
#include "game/stage.h"
#include "game/world.h"

#include <algorithm>


 EntityEnemy::EntityEnemy(EnemyType type) : EntityCollider(){
    if (type == NORMAL) {
        Mesh* mesh = Mesh::Get("data/Kenney/Models/OBJ format/enemy_ufoRed.obj");
        SetMesh(mesh, {});
        velocity = 3;
        health = 5;
        model.setTranslation(Vector3(-5, 0.3, 0));
        model.scale(0.7, 0.7, 0.7);
    }
    else if (type == STRONG) {
        Mesh* mesh = Mesh::Get("data/Kenney/Models/OBJ format/enemy_ufoGreen.obj");
        SetMesh(mesh, {});
        velocity = 1.5;
        health = 10;
        model.setTranslation(Vector3(-5, 0.3, 0));
        model.scale(1.2, 1.2, 1.2);
    }
    else if (type == FAST) {
        Mesh* mesh = Mesh::Get("data/Kenney/Models/OBJ format/enemy_ufoPurple.obj");
        SetMesh(mesh, {});
        velocity = 6;
        health = 3;
        model.setTranslation(Vector3(-5, 0.3, 0));
        model.scale(0.7, 0.7, 0.7);
    }
}

void EntityEnemy::update(float seconds_elapsed){
    
    std::vector< Vector3 > points = World::GetInstance()->waypoints;
   
    
    if(points.size() != 0 & waypoint_index != points.size()){
        
            Vector3 origin = model.getTranslation();
            Vector3 target = points[waypoint_index];

            // Orient before translating!
            float angle = model.getYawRotationToAimTo(target);
            model.rotate(angle*seconds_elapsed*100, Vector3(0, 1, 0));
            
            model.translate(0.f, 0.f, seconds_elapsed*velocity);
            
            float distance_to_target = (target - origin).length();

            if (distance_to_target < 0.7f) {
                waypoint_index++;
            }
        }
}

void EntityEnemy::GetDamage(int damage) {
	health -= damage;
	if (health <= 0) {
		Die();
	}
}

void EntityEnemy::Die() {
	World::GetInstance()->removeEntity(this);
	World::GetInstance()->RemoveEnemy(this);
	delete this;
}



void EntityEnemy::followPath(float seconds_elapsed){
    
    


}
    
    

