#include <fstream>
#include <string>
#include <ncursesw/ncurses.h>
#pragma once

#define H 28
#define W 100

class Level
{
public:
	std::string room[H]{};
	Level(){
		std::ifstream room_file;
		room_file.open("room.txt");
		if(room_file.is_open()){
			int i = 0;
			while(getline(room_file, room[i]) && i < H)
				i++;
		}
		room_file.close();
	}
	void print_level(){
		for(int i = 0; i < H; i++){
			for(int j = 0; j < W; j++){
				mvaddch(i+1, j+1 , room[i][j]);
			}
		}
	}
	void check_collision(int x, int y){
		//room[1][1];
		//return;
		if(x < W && y < H && x > 0 && y > 0){
//			if(room[y+1][x] == '#')
			mvaddstr(15, 15, std::to_string(x).c_str());
			mvaddstr(16, 15, std::to_string(y).c_str());
			mvaddstr(17, 15, room[1].c_str());

		} else {
			mvaddch(15, 15, 'n');
		}
	}
};