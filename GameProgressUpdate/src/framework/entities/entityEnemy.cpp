#include "entityEnemy.h"
#include "entityMesh.h"
#include "framework/camera.h"
#include "graphics/mesh.h"
#include "graphics/shader.h"
#include "game/stage.h"
#include "game/world.h"

#include <algorithm>

void EntityEnemy::update(float seconds_elapsed){
    
    std::vector< Vector3 > points = World::GetInstance()->waypoints;
   
    
    if(points.size() != 0 & waypoint_index != points.size()){
        
            Vector3 origin = model.getTranslation();
            Vector3 target = points[waypoint_index];

            // Orient before translating!
            float angle = model.getYawRotationToAimTo(target);
            model.rotate(angle, Vector3(0, 1, 0));
            
            model.translate(0.f, 0.f, seconds_elapsed);
            
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
    
    
