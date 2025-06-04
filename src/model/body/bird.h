#ifndef FLAPPY_BIRD_BIRD_H
#define FLAPPY_BIRD_BIRD_H

#include "body.h"

class Bird : public Body {
public:
    Bird(std::map<std::string, float> &data);

    Body *fabric_method(float x, float y, float x_velocity, float y_velocity) const;
    int type() const;

    bool is_collision(Body& another) const;
};


#endif //FLAPPY_BIRD_BIRD_H
