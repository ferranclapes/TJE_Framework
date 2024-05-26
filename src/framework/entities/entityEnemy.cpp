#include "entityEnemy.h"
#include "entityMesh.h"
#include "framework/camera.h"
#include "graphics/mesh.h"
#include "graphics/shader.h"
#include "game/stage.h"
#include "game/world.h"

#include <algorithm>

void EntityEnemy::update(float seconds_elapsed){

    if (World::GetInstance()->waypoints.size() != 0) {


        Vector3 origin = model.getTranslation();
        Vector3 target = World::GetInstance()->waypoints[waypoint_index];

        // Orient before translating!
        if (last_waypoint < waypoint_index) {
            float angle = model.getYawRotationToAimTo(target);
            model.rotate(angle, Vector3(0, 1, 0));
            std::cout << "Angle = " << angle << '\n';
        }

        model.translate(0, 0, seconds_elapsed);

        float distance_to_target = target.distance(origin);
        //std::cout << "Distance = " << distance_to_target << '\n';

        last_waypoint = waypoint_index;

        if (distance_to_target < 0.1f) {
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
    
    

