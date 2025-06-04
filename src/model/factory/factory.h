#ifndef FLAPPY_BIRD_FACTORY_H
#define FLAPPY_BIRD_FACTORY_H

#include "../body/body.h"

class Model;

class Factory {
public:

    virtual Body* create_bird(std::map<std::string, float>& data) = 0;
    virtual std::pair<Body*, Body*> create_pipe_pair() const = 0;

    virtual Body* create_top_pipe(std::map<std::string, float>& data) = 0;
    virtual Body* create_bottom_pipe(std::map<std::string, float>& data) = 0;

    virtual void set_model(Model *model) = 0;
    virtual Model *get_model() const = 0;

    virtual ~Factory() {}
};


#endif //FLAPPY_BIRD_FACTORY_H
