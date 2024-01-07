#include "entity.h"
class Projectile : public Entity{
public:
    coords position;
    char direction;

    Projectile(int pos_x, int pos_y, float spd, int hp, char repr, int dim_x, int dim_y, Level* rom = nullptr, char dir) : Entity(pos_x, pos_y, spd, repr, dim_x, dim_y, rom){
        position.x = pos_x;
        position.y = pos_y;
        direction = dir; 
    }

};