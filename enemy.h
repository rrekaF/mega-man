#include "character.h"
#pragma once

class Enemy : public Character{
public:
    using Character::Character;

    int tick() override{
        gravity();
        print_entity();

        return 0;

    }
};
