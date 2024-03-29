#include "projectile.h"
#include "enemy.h"

#define ENEMY_TIMER 30
#define N_ENEMY_SPAWNS 4
#define SHOOT_COOLDOWN 20
#define SHIELD_DURATION 30
#define GRAVITY 0.5

class Player : public Character
{
	using Character::Character;
	std::vector<Projectile*> projectiles;
	std::vector<Enemy*> enemies;
	int shield = SHIELD_DURATION;
	int shoot_cooldown = SHOOT_COOLDOWN;
	int enemy_timer = ENEMY_TIMER;
	coords possible_enemy_spawns[N_ENEMY_SPAWNS] = {
		{5, 5},
		{40, 6},
		{70, 20},
		{60, 13}
	};

public:
	int movement_handler()
	{
		int input = getch();
		if (input != ERR)
		{
			switch (input)
			{
			case KEY_UP:
				if(room->check_collision(position.x, position.y + 1)){
					y_momentum = GRAVITY;
				}
				break;
			case KEY_DOWN:
				enemies.push_back(new Enemy(5, 5, 1, 1, '$', 1, 2, room));
				break;
			case KEY_LEFT:
				move(position.x - 1, position.y);
				break;
			case KEY_RIGHT:
				move(position.x + 1, position.y);
				break;
			case 'a':
				shoot(input);
				break;
			case 'd':
				shoot(input);
				break;
			case 'q':
				delete_enemy(0);
				break;
			default:
				break;
      		}
		}
		return 0;
	}
	void shoot(char dir){
		if(!shoot_cooldown){
			projectiles.push_back(new Projectile(position.x, position.y - 1, 1, 100, '-', 1, 1, dir, room));
			shoot_cooldown = SHOOT_COOLDOWN;
		}
	}
	int tick() override {
		if(enemy_timer){
			enemy_timer--;
		}else{
			srand(time(0));
			int spawn = rand() % N_ENEMY_SPAWNS;
			enemies.push_back(new Enemy(possible_enemy_spawns[spawn].x, possible_enemy_spawns[spawn].y, 1, 1, '$', 1, 2, room));
			enemy_timer = ENEMY_TIMER;
		}
		if(shoot_cooldown){
			shoot_cooldown--;
		}
		gravity();
		if(shield){
			shield--;
		}
		mvaddstr(position.y - 3,  position.x, std::to_string(shield).c_str());
		if(health <= 0){
			return 1;
		}
		check_enemy_collision();
		print_entity();
		print_hp();
		projectiles_handler();
		enemies_handler();

		return movement_handler();
	}
	void check_enemy_collision(){
		for(auto enemy : enemies){
			for(auto cord : enemy->occupied_space){
				for(auto my_cord : occupied_space){
					if(cord.x == my_cord.x && cord.y == my_cord.y){
						if(!shield){
							health -= 1;
							occupied_space = last_occupied_space;
							shield = SHIELD_DURATION;
						}
					}
				}
			}
		}
		
	}
	void delete_enemy(int idx){
		Enemy* tmp = enemies[idx];
		enemies.erase(enemies.begin() + idx);
		delete tmp;
	}
	void delete_projectile(int idx){
		Projectile* tmp = projectiles[idx];
		projectiles.erase(projectiles.begin() + idx);
		delete tmp;
	}
	int projectile_hit(int x, int y){
		for(int i = 0; i < enemies.size(); i++){
			for(auto j : enemies[i]->occupied_space){
				if( j.x == x && j.y == y){
					return i;
				}
			}
		}
		return -1;
	}
	void projectiles_handler(){
		for(int i = 0; i < projectiles.size(); i++){
			int hit = projectile_hit(projectiles[i]->position.x, projectiles[i]->position.y);
			if(projectiles[i]->inbounds() == 0 || hit != -1){
				delete_projectile(i);
			}
			if(hit != -1){
				enemies[hit]->health -= 1;
			}
		}
		for(auto i : projectiles){
			i->tick();
		}
	}
	void enemies_handler(){
		for(int i = 0; i < enemies.size(); i++){
			if(enemies[i]->health <= 0){
				delete_enemy(i);
			}
		}
		for(auto i : enemies){
			i->tick();
			i->move_towards_player(position.x, position.y);
		}

	}


};
