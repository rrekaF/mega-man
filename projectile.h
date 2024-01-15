#include "entity.h"
#pragma once
class Projectile : public Entity{
public:
    char direction;

    Projectile(int pos_x, int pos_y, float spd, int hp, char repr, int dim_x, int dim_y, char dir, Level* rom = nullptr) : Entity(pos_x, pos_y, spd, repr, dim_x, dim_y, rom){
        direction = dir;
    }
    int tick() override {
        print_entity();
        Projectile::move();
        return 0;
    }
    bool inbounds(){
        return !(room->check_collision(position.x, position.y));
    }
    void move(){
        if(direction == 'a'){
            position.x -= 1;
        } else {
            position.x += 1;
        }
    }
    

};