#ifndef FLAPPY_BIRD_SIMPLE_FACTORY_H
#define FLAPPY_BIRD_SIMPLE_FACTORY_H

#include "factory.h"

class Model;

class Simple_Factory : public Factory {
public:
    Simple_Factory();

    Body *create_bird(std::map<std::string, float> &data);
    std::pair<Body *, Body *> create_pipe_pair() const;

    Body *create_top_pipe(std::map<std::string, float> &data);
    Body *create_bottom_pipe(std::map<std::string, float> &data);

    void set_model(Model *model);
    Model *get_model() const;

    ~Simple_Factory();
private:
    Model* model;
    float gap;

    Body* top_pipe;
    Body* bottom_pipe;
};


#endif //FLAPPY_BIRD_SIMPLE_FACTORY_H
