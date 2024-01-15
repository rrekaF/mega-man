#include <vector>
#include "level.h"
#pragma once
struct coords
{
	int x;
	int y;
};
class Entity{
public:
    coords position;
    std::vector<coords> occupied_space;
	std::vector<coords> last_occupied_space;
    char representation;
    int dimensions_x, dimensions_y;
	float speed;
    Level* room;

    Entity(int pos_x, int pos_y, float spd, char repr, int dim_x, int dim_y, Level* rom = nullptr){
        position.x = pos_x;
		position.y = pos_y;
		speed = spd;
        representation = repr;
		dimensions_x = dim_x;
		dimensions_y = dim_y;
        room = rom;
        fill_space(dimensions_x, dimensions_y);
    }
	int virtual tick() = 0;
    void print_entity()
	{

		fill_space(dimensions_x, dimensions_y);
		for (auto i : occupied_space)
			mvaddch(i.y, i.x, representation);
	}
	void move(int new_x, int new_y){
		if(!room->check_collision(new_x, new_y)){
			position.y = new_y;
			position.x = new_x;
		}
	}

	void print_position(){
		mvaddstr(9, 10, "pos");
		mvaddstr(10, 10, std::to_string(position.x).c_str());
		mvaddstr(11, 10, std::to_string(position.y).c_str());
	}
private:
	void fill_space(int dimensions_x, int dimensions_y)
	{
		last_occupied_space = occupied_space;
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
};