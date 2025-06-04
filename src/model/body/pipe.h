#ifndef FLAPPY_BIRD_PIPE_H
#define FLAPPY_BIRD_PIPE_H

#include "body.h"

class Pipe : public Body {
public:
    Pipe(std::map<std::string, float> &data);

    virtual Body *fabric_method(float x, float y, float x_velocity, float y_velocity) const;
    virtual int type() const;
};


#endif //FLAPPY_BIRD_PIPE_H
