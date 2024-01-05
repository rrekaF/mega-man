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
				position.y -= speed;
				y_momentum = 1;
				break;
			case KEY_DOWN:
				position.y += speed;
				break;
			case KEY_LEFT:
				position.x -= speed;
				break;
			case KEY_RIGHT:
				position.x += speed;
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
