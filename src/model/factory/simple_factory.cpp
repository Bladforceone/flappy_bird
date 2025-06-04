#include "simple_factory.h"
#include "../body/bird.h"
#include "../body/pipe.h"
#include "../model.h"


Body *Simple_Factory::create_bird(std::map<std::string, float> &data){
    auto bird = new Bird(data);
    if (gap == 0)
        gap = 5.0f * bird->get_height();
    return bird;
}

std::pair<Body *, Body *> Simple_Factory::create_pipe_pair() const {
    if (!top_pipe || !bottom_pipe)
        return std::pair<Body *, Body *>();

    int r = rand() % 275 + 75;

    auto _bottom_pipe = bottom_pipe->fabric_method(model->get_size().first, r, -3, 0);
    auto _top_pipe = top_pipe->fabric_method(model->get_size().first, r + gap, -3, 0);

    return std::make_pair(_top_pipe, _bottom_pipe);
}

Body *Simple_Factory::create_top_pipe(std::map<std::string, float> &data) {
    auto top_pipe = new Pipe(data);
    
    if (!this->top_pipe)
        this->top_pipe = top_pipe->fabric_method(0, 0, 0, 0);
    
    return top_pipe;
}

Body *Simple_Factory::create_bottom_pipe(std::map<std::string, float> &data) {
    auto bottom_pipe = new Pipe(data);

    if (!this->bottom_pipe)
        this->bottom_pipe = bottom_pipe->fabric_method(0, 0, 0, 0);

    return bottom_pipe;
}

Simple_Factory::Simple_Factory() : model(nullptr), top_pipe(nullptr), bottom_pipe(nullptr), gap(0) {}

Simple_Factory::~Simple_Factory() {
    delete top_pipe;
    delete bottom_pipe;
}

void Simple_Factory::set_model(Model *model) {
    if (!this->model)
        this->model = model;
}

Model *Simple_Factory::get_model() const {
    return model;
}
