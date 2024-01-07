#include "character.h" // just for coords, TODO put coords into seperate file or import only coords from character
class Projectile{
public:
    coords position;
    char direction;

    Projectile(int x, int y, char dir){
        position.x = x;
        position.y = y;
        direction = dir; 
    }

}