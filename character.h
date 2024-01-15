#include <ncursesw/ncurses.h>
#include <cmath>
#include <string>
#include "entity.h"

class Character : public Entity
{
	using Entity::Entity;
public:
	short int health;
	short int max_health;
	// std::vector<coords> last_occupied_space;
	float y_momentum;

	Character(int pos_x, int pos_y, float spd, int hp, char repr, int dim_x, int dim_y, Level* rom = nullptr,  float y_mom=-1) : Entity(pos_x, pos_y, spd, repr, dim_x, dim_y, rom){
		health = hp;
		max_health = hp;
		y_momentum = y_mom;
	}

	void print_hp(){
		mvaddstr(position.y - 2, position.x - 1, std::to_string(health).c_str());
        mvaddch(position.y - 2, position.x, '/');
        mvaddstr(position.y - 2, position.x + 1, std::to_string(max_health).c_str());
	}
	void print_momentum(){
		mvaddstr(4,5, "mom");
		mvaddstr(5, 5, std::to_string(y_momentum).c_str());
	}
	void gravity(){
	
		if(y_momentum > 0){
			y_momentum *= !room->check_collision(position.x, position.y - dimensions_y);
			position.y -= int(ceil(y_momentum));
		} else {
			position.y -= int(round(y_momentum));
		}
		if(y_momentum > -1){
			y_momentum -= 0.05;
		}
		y_momentum *= !room->check_collision(position.x, position.y + 1);

	}



};