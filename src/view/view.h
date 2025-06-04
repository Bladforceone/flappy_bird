#ifndef FLAPPY_BIRD_VIEW_H
#define FLAPPY_BIRD_VIEW_H

#include "../state.h"


class View {
public:
    virtual bool is_alive() = 0;

    virtual int get_action() const = 0;
    virtual std::pair<int, int> get_size() const = 0;
    virtual std::pair<std::pair<float, float>, std::pair<float, float>> get_bird_size() const = 0;
    virtual std::pair<std::pair<float, float>, std::pair<float, float>> get_pipe_size() const = 0;

    virtual void show_state(State& state) = 0;

    virtual ~View() {};
};


#endif //FLAPPY_BIRD_VIEW_H
