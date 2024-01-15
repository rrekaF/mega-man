#include "character.h"
#include "projectile.h"
#include <iostream>

class Player : public Character
{
	using Character::Character;
	std::vector<Projectile*> projectiles;

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
				projectiles.push_back(new Projectile(position.x, position.y - 1, 1, 100, '-', 1, 1, 'a', room));
				break;
			case 'd':
				projectiles.push_back(new Projectile(position.x, position.y - 1, 1, 100, '-', 1, 1, 'd', room));
				break;
			case 'q':
				return 1;
			default:
				break;
      		}
		}
		return 0;
	}
	int tick() override {
		gravity();
		print_entity();
		print_position();
		for(int i = 0; i < projectiles.size(); i++){
			if(projectiles[i]->inbounds() == 0){
				Projectile* tmp = projectiles[i];
				projectiles.erase(projectiles.begin() + i);
				delete tmp;
			}
		}
		print_projectiles();
		return movement_handler();
	}
	void print_projectiles(){
		for(auto i : projectiles){
			i->tick();
		}
	}


};
