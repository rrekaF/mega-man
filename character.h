#include <ncursesw/ncurses.h>
#include <cmath>
#include <string>
#include "entity.h"

class Character : public Entity
{
	using Entity::Entity;
public:
	short int health;
	// std::vector<coords> last_occupied_space;
	float y_momentum;

	Character(int pos_x, int pos_y, float spd, int hp, char repr, int dim_x, int dim_y, Level* rom = nullptr,  float y_mom=-1) : Entity(pos_x, pos_y, spd, repr, dim_x, dim_y, rom){
		health = hp;
		y_momentum = y_mom;
	}

	void shoot(char direction){
		switch (direction){
		case 'a':
			/* code */
			break;
		
		default:
			break;
		}
	}
	void gravity(){
	
		if(y_momentum > 0){
			y_momentum *= !room->check_collision(position.x, position.y - dimensions_y);
			position.y -= int(ceil(y_momentum));
		} else {
			position.y -= int(ceil(y_momentum));
		}
		if(y_momentum > -1){
			y_momentum -= 0.1;
		}
		y_momentum *= !room->check_collision(position.x, position.y + 1);

	}



};