#include "entityEnemy.h"
#include "entityMesh.h"
#include "framework/camera.h"
#include "graphics/mesh.h"
#include "graphics/shader.h"
#include "game/stage.h"
#include "game/world.h"
#include "entityUI.h"
#include "game/game.h"

#include <algorithm>


 EntityEnemy::EntityEnemy(EnemyType type) : EntityCollider(){
    if (type == NORMAL) {
        Mesh* mesh = Mesh::Get("data/Kenney/Models/OBJ format/enemy_ufoRed.obj");
        SetMesh(mesh, {});
        velocity = 3;
        health = 5;
        maxHealth = 5;
        model.setTranslation(Vector3(-11, 0.3, 13.33));
        model.scale(0.7, 0.7, 0.7);
       
    }
    else if (type == STRONG) {
        Mesh* mesh = Mesh::Get("data/Kenney/Models/OBJ format/enemy_ufoGreen.obj");
        SetMesh(mesh, {});
        velocity = 1.5;
        health = 10;
        maxHealth = 10;
        model.setTranslation(Vector3(-11, 0.3, 11.33));
        model.scale(1.2, 1.2, 1.2);
    }
    else if (type == FAST) {
        Mesh* mesh = Mesh::Get("data/Kenney/Models/OBJ format/enemy_ufoPurple.obj");
        SetMesh(mesh, {});
        velocity = 6;
        health = 3;
        maxHealth = 3;
        model.setTranslation(Vector3(-11, 0.3, 11.33));
        model.scale(0.7, 0.7, 0.7);
    }
     
     vida_m.color = Vector4(0, 1, 0, 0);
     vida_m.shader = Shader::Get("data/shaders/example.vs", "data/shaders/health-bar.fs");
     vida = new EntityUI(0.5f, 0.0f, 0.15f, 0.04f, vida_m);
     this->addChild(vida);
     
}

void EntityEnemy::update(float seconds_elapsed){
    
    std::vector< Vector3 > points = World::GetInstance()->waypoints;
   
    
    if (points.size() != 0 && waypoint_index != points.size()) {

        Vector3 origin = model.getTranslation();
        Vector3 target = points[waypoint_index];

        // Orient before translating!
        float angle = model.getYawRotationToAimTo(target);
        model.rotate(angle * seconds_elapsed * 100, Vector3(0, 1, 0));


        model.translate(0.f, 0.0f, seconds_elapsed * velocity);

        float distance_to_target = (target - origin).length();

        if (distance_to_target < 0.4f) {
            waypoint_index++;
        }
    }
    
   
    Vector3 pos3D = model.getTranslation();
    pos3D.y += 0.9;
    
    int width = Game::GetInstance()->window_width;
    int height = Game::GetInstance()->window_height;

    
    Vector4 pos2D = Camera::current->viewprojection_matrix * Vector4(pos3D, 1.0);
    vida->pos_x = pos2D.x / pos2D.w;
    vida->pos_y = pos2D.y / pos2D.w;
    vida->mask = float(health) / float(maxHealth);

    vida->quad->createQuad(vida->pos_x, vida->pos_y, 0.15f, 0.04f, false);

    
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
    
    

