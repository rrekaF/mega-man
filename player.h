#include "character.h"
#include <iostream>

class Player : public Character
{
	using Character::Character;

public:
	int movement_handler()
	{
		print_momentum();
		print_position();
		gravity();
		int input = getch();
		if (input != ERR)
		{
			switch (input)
			{
			case KEY_UP:
				y_momentum = 0.3;
				break;
			case KEY_DOWN:
				// Unused as of now
				break;
			case KEY_LEFT:
				move(position.x - 1, position.y);
				break;
			case KEY_RIGHT:
				move(position.x + 1, position.y);
				break;
			case 'a':
				break;
			case 'd':
				break;
			case 'q':
				return 1;
			default:
				break;
      		}
		}
		return 0;
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
	void print_momentum(){
		mvaddstr(4,5, "mom");
		mvaddstr(5, 5, std::to_string(y_momentum).c_str());
	}
	void print_position(){
		mvaddstr(9, 10, "pos");
		mvaddstr(10, 10, std::to_string(position.x).c_str());
		mvaddstr(11, 10, std::to_string(position.y).c_str());
	}

};
