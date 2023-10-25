#include "raymath.h"
#include "Food.h"

class Food {
public:
    Vector2 location;
    bool isCollected;

    Food(Vector2 loco, bool collection) {
        location = loco;
        isCollected = collection;
    }

    Food() {
        location = (Vector2){ 0,0 };
        isCollected = false;
    }
};