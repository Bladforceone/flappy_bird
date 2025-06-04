#include "pipe.h"

Body *Pipe::fabric_method(float x, float y, float x_velocity, float y_velocity) const {
    Pipe* pipe = new Pipe(*this);

    pipe->set_x_velocity(x_velocity);
    pipe->set_y_velocity(y_velocity);
    pipe->set_x(x);
    pipe->set_y(y);

    return pipe;
}

int Pipe::type() const {
    return get_texture_height_scale() > 0 ? 1 : 2;
}

Pipe::Pipe(std::map<std::string, float> &data) : Body(data) {
    set_x_velocity(-3);
    set_y_velocity(0);
}
