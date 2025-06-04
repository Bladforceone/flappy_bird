#ifndef FLAPPY_BIRD_BODY_H
#define FLAPPY_BIRD_BODY_H

#include "map"
#include "string"

class Body {
public:
    Body(std::map<std::string, float>& data);

    virtual Body* fabric_method(float x, float y, float x_velocity, float y_velocity) const = 0;
    virtual int type() const = 0;

    virtual std::map<std::string, float> get_state() const;
    float get_width() const;
    float get_height() const;
    float get_x() const;
    float get_y() const;
    float get_texture_width_scale() const;
    float get_texture_height_scale() const;
    float get_x_velocity() const;
    float get_y_velocity() const;
    float get_top_left_x() const;
    float get_top_left_y() const;

    void move();
    void set_x_velocity(float velocity);
    void set_y_velocity(float velocity);
    void set_x(float x);
    void set_y(float y);

    virtual ~Body();
private:
    float x;
    float y;

    float x_velocity;
    float y_velocity;

    int texture_width;
    int texture_height;

    float texture_width_scale;
    float texture_height_scale;
};


#endif //FLAPPY_BIRD_BODY_H
