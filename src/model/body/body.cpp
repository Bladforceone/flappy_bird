#include "body.h"
#include "cmath"

Body::Body(std::map<std::string, float> &data):
    x(data.find("x") != data.end() ? data["x"] : 0),
    y(data.find("y") != data.end() ? data["y"] : 0),
    x_velocity(data.find("x_velocity") != data.end() ? data["x_velocity"] : 0),
    y_velocity(data.find("y_velocity") != data.end() ? data["y_velocity"] : 0),
    texture_width(data.find("texture_width") != data.end() ? data["texture_width"] : 0),
    texture_height(data.find("texture_height") != data.end() ? data["texture_height"] : 0),
    texture_width_scale(data.find("texture_width_scale") != data.end() ? data["texture_width_scale"] : 1),
    texture_height_scale(data.find("texture_height_scale") != data.end() ? data["texture_height_scale"] : 1)
{

}

std::map<std::string, float> Body::get_state() const {
    std::map<std::string, float> state;

    state["x"] = x;
    state["y"] = y;
    state["type"] = type();

    return state;
}

float Body::get_width() const {
    return abs(texture_width * texture_width_scale);
}

float Body::get_height() const {
    return abs(texture_height * texture_height_scale);
}

float Body::get_x() const {
    return x;
}

float Body::get_y() const {
    return y;
}

float Body::get_top_left_x() const {
    if (texture_width_scale > 0)
        return get_x();
    return get_x() + get_width();
}

float Body::get_top_left_y() const {
    if (texture_height_scale > 0)
        return get_y();
    return get_y() + get_height();

}

void Body::move() {
    x += x_velocity;
    y += y_velocity;
}

void Body::set_x_velocity(float velocity) {
    x_velocity = velocity;
}

void Body::set_y_velocity(float velocity) {
    y_velocity = velocity;
}

Body::~Body() {

}

void Body::set_x(float x) {
    Body::x = x;
}

void Body::set_y(float y) {
    Body::y = y;
}

float Body::get_x_velocity() const {
    return x_velocity;
}

float Body::get_y_velocity() const {
    return y_velocity;
}

float Body::get_texture_width_scale() const {
    return texture_width_scale;
}

float Body::get_texture_height_scale() const {
    return texture_height_scale;
}
