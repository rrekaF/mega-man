#include "character.h"
#pragma once

class Enemy : public Character{
public:
    using Character::Character;
    int move_timer = 0;

    int tick() override{
        gravity();
        print_entity();
        if(move_timer){
            move_timer--;
        }

        return 0;
    }
    void move_towards_player(int x, int y){
        if(move_timer){
            return;
        }
        char mv;
        if(x > position.x){
            if(room->check_collision(position.x + 1, position.y)){
                move_up();
            }
            move_right();
            move_timer = 10;
        } else {
            if(room->check_collision(position.x - 1, position.y)){
                move_up();
            }
            move_left();
            move_timer = 5;
        }

        if(y > position.y){
            move_up();
        }
    }
    void check_collision_enemies(){
        
    }
    void move_up(){
        if(room->check_collision(position.x, position.y + 1)){
			y_momentum = 0.5;
		}
    }
    void move_left(){
        move(position.x - 1, position.y);
    }
    void move_right(){
        move(position.x + 1, position.y);
    }
};
