A mega-man type of game created as a project for PRG on PJATK Gdańsk.
It's using ncurses C++ library for graphics.

# Installation

## Installing ncurses:
### Linux
Arch:
~~~sh
sudo pacman -S ncurses
~~~
Debian:
~~~sh
sudo apt-get install ncurses
~~~
### Windows
~~~
TODO
~~~
## Cloning repository:
~~~sh
git clone https://github.com/rrekaF/mega-man
~~~

## Compiling and running:
### Linux:
~~~sh
cd ./mega-man
sudo chmod +x compile_and_run.sh
./compile_and_run.sh
./mega-man
~~~

Alternatively if you don't want to use my script you could compile it yourself, remember to link ncurses with -lncurses like so:

~~~sh
g++ main.cpp -o "mega-man" -lncurses && ./mega-man
~~~
### Windows:
~~~
TODO
~~~

# Delta
Everything from the player through enemies to projectiles uses time to determine it's position.
Ex.
~~~cpp
			switch (input)
			{
			case KEY_UP:
				position.y -= speed * delta;
				break;
			(...)
			}
~~~
In the above example from player.h I check whether the key pressed is the up arrow and if so the player moves up by a distance determined by it's speed and the number of ms since last frame. This way no matter the frame rate, the object will move at the same speed.

I determine the delta by using 
~~~cpp
delta = duration_cast<milliseconds>(now() - last_check).count();
last_check = now()
~~~

The last_check is initialized before the game loop starts so the first time duration_cast is called it doesn't return the value i need but in practice it doesn't make a difference.

The .count() method returns an integer instead of std::chrono::duration object.

# Dimensions and occupied_space
Because i wanted some characters to be more than 1x1 in size i decided to have the bottom left corner of a character object be its position and have their dimensions separate as a pair of integers representing width (x) and height (y). I then have a method called fill_space() that based on character object's position and dimensions figures out the space it occupies and appends coordinates of each of its cells to a vector called occupied_space. Thanks to that whenever i check for collision i can just check if coordinates one objects wants to go to are in another object's occupied_space vector and if so, disallow that.

![alt text](https://github.com/rrekaF/mega-man/blob/master/Documentation/fill_space_explanation.jpeg?raw=true)
