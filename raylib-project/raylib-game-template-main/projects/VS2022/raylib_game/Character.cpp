#include "Food.cpp"
#include <string>
#include <stdio.h>
#include <float.h>

class Character {
public:
    Vector2 ghostPoint;
    Vector2 location;
    Vector2 velocity;
    Vector2 acceleration;
    Vector2 closest;
    float maxforce;
    float maxspeed;
    float angle;
    float recharge;
    float food;
    float rechargeRate;
    bool alive;
    bool promoted;
    bool mutated;
    int type;
    int vision;
    float distances[50];
    int indexClosest;
    int grab;


    Character()
    {

    }
    Character(float x, float y, int typ) {
        promoted = false;
        mutated = false;
        type = typ;
        if (typ == 0)
        {
            grab = 25;
            maxspeed = 4.5f;
            maxforce = 1.0f;
            ghostPoint = (Vector2){ x,y };
            acceleration = (Vector2){ 0, 0 };
            velocity = (Vector2){ 0, 0 };
            location = (Vector2){ x, y };
            angle = 0;
            recharge = 60;
            food = 0;
            rechargeRate = 1;
            alive = true;
            vision = 0;
        }
        if (typ == 1)
        {
            grab = 5;
            maxspeed = 2.0f;
            maxforce = 0.6f;
            ghostPoint = (Vector2){ x,y };
            acceleration = (Vector2){ 0, 0 };
            velocity = (Vector2){ 0, 0 };
            location = (Vector2){ x, y };
            angle = 0;
            recharge = 60;
            food = 0;
            rechargeRate = 1;
            alive = true;
            vision = 50;
        }
    }

    Character(float x, float y, int typ, Character hare, Character tor)
    {
        mutated = true;
        float deltaX = hare.location.x - tor.location.x;
        float deltaY = hare.location.y - tor.location.y;
        float dist = sqrtf((deltaX * deltaX) + (deltaY * deltaY));
        grab = ((hare.grab+tor.grab)/2) * sqrtf(sqrtf(sqrtf(101-dist)));
        maxspeed = ((hare.maxspeed + tor.maxspeed) / 2) * sqrtf(sqrtf(sqrtf(101 - dist)));
        maxforce = ((hare.maxforce + tor.maxforce) / 2) * sqrtf(sqrtf(sqrtf(101 - dist)));
        ghostPoint = (Vector2){ x,y };
        acceleration = (Vector2){ 0, 0 };
        velocity = (Vector2){ 0, 0 };
        location = (Vector2){ x, y };
        angle = 0;
        recharge = 60;
        food = 0;
        rechargeRate = 1;
        alive = true;
        vision = (tor.vision * 0.8f) * sqrtf(sqrtf(sqrtf(101 - dist)));
        type = typ;
    }

    void update() {
        velocity = Vector2Add(velocity, acceleration);
        float mag = sqrtf(velocity.x * velocity.x + velocity.y * velocity.y);
        if (mag > maxspeed) {
            velocity = Vector2Normalize(velocity);
            velocity = Vector2Scale(velocity, maxspeed);
        }
        location = Vector2Add(location, velocity);
        acceleration = Vector2Scale(acceleration, 0);
        angle = 180 / PI * (atan2f(velocity.y, velocity.x) + PI / 2);
    }

    void update(Food* foods) {
        velocity = Vector2Add(velocity, acceleration);
        float mag = sqrtf(velocity.x * velocity.x + velocity.y * velocity.y);
        if (mag > maxspeed) {
            velocity = Vector2Normalize(velocity);
            velocity = Vector2Scale(velocity, maxspeed);
        }
        location = Vector2Add(location, velocity);
        acceleration = Vector2Scale(acceleration, 0);
        angle = 180 / PI * (atan2f(velocity.y, velocity.x) + PI / 2);



        //create a parallel of distances of food
        for (int i = 0; i < 50;i++)
        {
            if(!foods[i].isCollected)
                distances[i] = findMagnitude(foods[i].location);
            else
            {
                distances[i] = FLT_MAX;
            }
        }

        //setting variables
        float closest = distances[0];
        indexClosest = 0;

        for (int i = 0; i < 50; i++)
        {
            if (closest > distances[i])
            {
                closest = distances[i];//iterate through array to see if there is anything actually closer
                indexClosest = i;//save the index of the closest food
            }
        }

        std::string text = "[" + std::to_string(distances[indexClosest]) + "]";
        //DrawText(text.c_str(), location.x, location.y-20, 12, MAGENTA);

        std::string blep = "Closest: " + std::to_string(distances[indexClosest]) + " Radius: " + std::to_string(vision);
        //DrawText(blep.c_str(), location.x, location.y-80, 18, MAGENTA);

        //if the closest is within the vision go seek the closest
        if (distances[indexClosest] < vision)
        {
            seek(foods[indexClosest], foods);
            std::string text = "SEEKING";
            // DrawText(text.c_str(), location.x, location.y+20, 12, BLUE);

        }
        else
        {
            seek();
            std::string text = "RANDOM SEEKING";
            // DrawText(text.c_str(), location.x, location.y+20, 12, BLUE);
        }
    }

    void seek() {
        if (abs(location.x - ghostPoint.x) < 100 && abs(location.y - ghostPoint.y) < 100)
        {
            float newX = 0;
            float newY = 0;
            while (newX < 100 || newX > 1500)
            {
                newX = location.x + (float)(rand() % 700 - 350);
            }
            while (newY < 100 || newY > 800)
            {
                newY = location.y + (float)(rand() % 700 - 350);
            }
            ghostPoint = (Vector2){newX, newY};
        }
        Vector2 desired = Vector2Subtract(ghostPoint, location);
        desired = Vector2Normalize(desired);
        desired = Vector2Scale(desired, maxspeed);
        Vector2 steer = Vector2Subtract(desired, velocity);
        float mag = sqrtf(steer.x * steer.x + steer.y * steer.y);
        if (mag > maxforce) {
            steer = Vector2Normalize(steer);
            steer = Vector2Scale(steer, maxforce);
        }
        acceleration = Vector2Add(acceleration, steer);
    }

    void seek(Food target, Food* foods) {
        Vector2 desired = Vector2Subtract(target.location, location);
        desired = Vector2Normalize(desired);
        desired = Vector2Scale(desired, maxspeed);
        Vector2 steer = Vector2Subtract(desired, velocity);
        float mag = sqrtf(steer.x * steer.x + steer.y * steer.y);
        if (mag > maxforce) {
            steer = Vector2Normalize(steer);
            steer = Vector2Scale(steer, maxforce);
        }
        acceleration = Vector2Add(acceleration, steer);
    }

    float findMagnitude(Vector2 vector)
    {
        return sqrtf((vector.x - location.x) * (vector.x - location.x) + (vector.y - location.y) * (vector.y - location.y));
    }
};