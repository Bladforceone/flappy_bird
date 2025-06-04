#include "bird.h"

bool collides_bottom(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {
    return (x1 + w1 >= x2 && x1 <= x2 + w2 && y1 - h1 >= y2 - h2  && y1 - h1 <= y2);
}

bool collides_top(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {
    return (x1 + w1 >= x2 && x1 <= x2 + w2 && y1 >= y2 - h2  && y1 - h1 <= y2);
}

Bird::Bird(std::map<std::string, float> &data) : Body(data) {}

Body *Bird::fabric_method(float x, float y, float x_velocity, float y_velocity) const {
    Bird *bird = new Bird(*this);

    bird->set_x_velocity(x_velocity);
    bird->set_y_velocity(y_velocity);
    bird->set_x(x);
    bird->set_y(y);

    return bird;
}

int Bird::type() const {
    return 0;
}

bool Bird::is_collision(Body &another) const {
    if (another.get_texture_height_scale() > 0)
        return collides_bottom(get_top_left_x(), get_top_left_y(), get_width(), get_height(), another.get_top_left_x(),
                    another.get_top_left_y(), another.get_width(), another.get_height());
    return collides_top(get_top_left_x(), get_top_left_y(), get_width(), get_height(), another.get_top_left_x(),
                           another.get_top_left_y(), another.get_width(), another.get_height());
}
