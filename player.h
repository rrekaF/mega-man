#include "character.h"
#include <iostream>

class Player : public Character
{
	using Character::Character;

public:
	int movement_handler()
	{
		gravity();
		int input = getch();
		if (input != ERR)
		{
			switch (input)
			{
			case KEY_UP:
				y_momentum = 0.5;
				break;
			case KEY_DOWN:
				// move(position.x, position.y += speed);
				break;
			case KEY_LEFT:
				move(position.x - 1, position.y);
				break;
			case KEY_RIGHT:
				move(position.x + 1, position.y);
				break;
			case 'q':
				return 1;
			default:
				break;
      		}
		}
		return 0;
	}

};
