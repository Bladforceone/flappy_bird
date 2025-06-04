#ifndef FLAPPY_BIRD_STATE_H
#define FLAPPY_BIRD_STATE_H

#include "map"
#include "vector"
#include "string"


struct State {
    std::map<std::string, float> bird;
    std::vector<std::map<std::string, float>> pipes;

    int score;
    int high_score;
    int step;

    bool is_jump;
    bool is_pipe_reached;
    bool is_fail;
    bool is_game_over;
};


#endif //FLAPPY_BIRD_STATE_H
