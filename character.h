#include <vector>
#include <ncursesw/ncurses.h>
#include <cmath>
#include <string>
#include "Level.h"
struct coords
{
	int x;
	int y;
};

class Character
{
public:
	coords position;
	short int health;
	std::vector<coords> occupied_space;
	std::vector<coords> last_occupied_space;
	char representation;
	int dimensions_x, dimensions_y;
	float speed;
	float y_momentum;
	Level* room;
	
	
	Character(int pos_x, int pos_y, float spd, int hp, char repr, int dim_x, int dim_y, Level* rom = nullptr, float y_mom=-1)
	{
		position.x = pos_x;
		position.y = pos_y;
		speed = spd;
		health = hp;
		representation = repr;
		dimensions_x = dim_x;
		dimensions_y = dim_y;
		y_momentum = y_mom;
		room = rom;
		fill_space(dimensions_x, dimensions_y);
	}

private:
	void fill_space(int dimensions_x, int dimensions_y)
	{
		std::vector<coords> new_occupied_space;
		coords piece_position;
		for (int i = 0; i < dimensions_y; i++)
		{
			for (int j = 0; j < dimensions_x; j++)
			{
				piece_position.x = position.x + j;
				piece_position.y = position.y - i;
				new_occupied_space.push_back(piece_position);
			}
		}
		occupied_space = new_occupied_space;
	}
public:
	void gravity(){
	
		if(y_momentum > 0){
			position.y -= int(ceil(y_momentum));
		} else {
			position.y -= int(ceil(y_momentum));
		}
		if(y_momentum > -1){
			y_momentum -= 0.2;
		}
		y_momentum *= !room->check_collision(position.x, position.y);
//		room->check_collision(position.x, position.y);
//		if(y_momentum < -1){
//			y_momentum = -1;
//		}
		
	}
	void print_character()
	{
		print_momentum();
		print_position();
		fill_space(dimensions_x, dimensions_y);
		for (auto i : occupied_space)
			mvaddch(i.y, i.x, representation);
	}
	void print_momentum(){
		mvaddstr(5, 5, std::to_string(y_momentum).c_str());
	}
	void print_position(){
		mvaddstr(10, 10, std::to_string(position.x).c_str());
		mvaddstr(11, 10, std::to_string(position.y).c_str());
	}

};