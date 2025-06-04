#ifndef FLAPPY_BIRD_MODEL_H
#define FLAPPY_BIRD_MODEL_H

#include "body/bird.h"
#include "factory/factory.h"
#include "vector"

struct State;

class Model {
public:
    static Model *default_model(const std::pair<int, int> &size,
                                const std::pair<std::pair<float, float>, std::pair<float, float>> &bird_texture,
                                const std::pair<std::pair<float, float>, std::pair<float, float>> &pipe_texture);

    Model(Factory *factory, const std::pair<int, int> &size,
          const std::pair<std::pair<float, float>, std::pair<float, float>> &bird_texture,
          const std::pair<std::pair<float, float>, std::pair<float, float>> &pipe_texture);

    void init();
    State update(int input);

    const std::pair<int, int> &get_size() const;
    const std::pair<std::pair<float, float>, std::pair<float, float>> &get_bird_texture() const;
    const std::pair<std::pair<float, float>, std::pair<float, float>> &get_pipe_texture() const;
    int get_step() const;
    int get_score() const;
    int get_high_score() const;

    bool is_jump() const;
    bool is_pipe_reached() const;
    bool is_fail() const;
    bool is_game_over() const;

    ~Model();
private:
    void restart();
    void start();
    void crash();

    void drop_bird();
    void check_and_fix_position();
    void count_score();
    void generate_pipes();
    void move_pipes();
    void remove_invisible_pipes();
    void check_crash();
    void jump();
    void parse_input(int input);

    Factory *factory;

    std::pair<int, int> size;
    std::pair<std::pair<float, float>, std::pair<float, float>> bird_texture;
    std::pair<std::pair<float, float>, std::pair<float, float>> pipe_texture;

    Bird *bird;
    std::vector<Body *> pipes;

    int state;
    bool _is_jump;
    bool _is_pipe_reached;
    bool _is_fail;

    int step;
    int score;
    int high_score;
};


#endif //FLAPPY_BIRD_MODEL_H
