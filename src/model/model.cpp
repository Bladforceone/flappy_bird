#include "model.h"
#include "../state.h"
#include "factory/simple_factory.h"
#include "algorithm"

Model *Model::default_model(const std::pair<int, int> &size,
                            const std::pair<std::pair<float, float>, std::pair<float, float>> &bird_texture,
                            const std::pair<std::pair<float, float>, std::pair<float, float>> &pipe_texture) {
    return new Model(new Simple_Factory(), size, bird_texture, pipe_texture);
}

Model::Model(Factory *factory, const std::pair<int, int> &size,
             const std::pair<std::pair<float, float>, std::pair<float, float>> &bird_texture,
             const std::pair<std::pair<float, float>, std::pair<float, float>> &pipe_texture) : factory(factory),
                                                                                                size(size),
                                                                                                bird_texture(
                                                                                                        bird_texture),
                                                                                                pipe_texture(
                                                                                                        pipe_texture),
                                                                                                bird(nullptr),
                                                                                                state(0),
                                                                                                _is_jump(false),
                                                                                                _is_pipe_reached(false),
                                                                                                _is_fail(false),
                                                                                                step(-1), score(0),
                                                                                                high_score(0) {
    factory->set_model(this);
}

const std::pair<int, int> &Model::get_size() const {
    return size;
}

const std::pair<std::pair<float, float>, std::pair<float, float>> &Model::get_bird_texture() const {
    return bird_texture;
}

const std::pair<std::pair<float, float>, std::pair<float, float>> &Model::get_pipe_texture() const {
    return pipe_texture;
}

bool Model::is_game_over() const {
    return state == 2;
}

bool Model::is_jump() const {
    return _is_jump;
}

bool Model::is_pipe_reached() const {
    return _is_pipe_reached;
}

bool Model::is_fail() const {
    return _is_fail;
}

int Model::get_step() const {
    return step;
}

int Model::get_score() const {
    return score;
}

int Model::get_high_score() const {
    return high_score;
}

void Model::init() {
    delete bird;
    for (auto pipe: pipes)
        delete pipe;
    pipes.clear();

    _is_fail = false;
    _is_jump = false;
    _is_pipe_reached = false;

    std::map<std::string, float> _bird, _top_pipe, _bottom_pipe;
    _bird["x"] = 0.3f * size.first;
    _bird["y"] = 0.5f * size.second;

    _bird["texture_width"] = bird_texture.first.first;
    _bird["texture_height"] = bird_texture.first.second;
    _bird["texture_width_scale"] = bird_texture.second.first;
    _bird["texture_height_scale"] = bird_texture.second.second;

    bird = (Bird*) factory->create_bird(_bird);

    _bottom_pipe["texture_width"] = pipe_texture.first.first;
    _bottom_pipe["texture_height"] = pipe_texture.first.second;
    _bottom_pipe["texture_width_scale"] = pipe_texture.second.first;
    _bottom_pipe["texture_height_scale"] = pipe_texture.second.second;

    _top_pipe = _bottom_pipe;
    _top_pipe["texture_height_scale"] = -pipe_texture.second.second;

    factory->create_top_pipe(_top_pipe);
    factory->create_bottom_pipe(_bottom_pipe);
}

Model::~Model() {
    delete factory;
    delete bird;
    for (auto pipe: pipes)
        delete pipe;
}

void Model::restart() {
    init();
    score = 0;
    state = 0;
}

void Model::start() {
    state = 1;
}

void Model::crash() {
    _is_fail = true;
    bird->set_y_velocity(0);
    state = 2;
}

void Model::drop_bird() {
    _is_jump = false;
    if (state != 1)
        return;
    bird->move();
    bird->set_y_velocity(bird->get_y_velocity() - 0.5);
}

void Model::jump() {
    _is_jump = true;
    bird->set_y_velocity(8);
}

void Model::check_and_fix_position() {
    _is_fail = false;
    if (state != 1)
        return;
    if (bird->get_y() > get_size().second) {
        bird->set_y(get_size().second);
        bird->set_y_velocity(0);
    }
    else if (bird->get_y() < 0)
        crash();
}

void Model::count_score() {
    _is_pipe_reached = false;
    if (state != 1)
        return;
    for (auto pipe: pipes) {
        if (!(pipe->get_x() - 1 <= bird->get_x() && pipe->get_x() + 1 >= bird->get_x()))
            continue;
        score += 1;
        _is_pipe_reached = true;
        if (score > high_score)
            high_score = score;
        break;
    }
}

void Model::generate_pipes() {
    if (state != 1)
        return;
    if (step % 150 != 0)
        return;
    auto pipe_pair = factory->create_pipe_pair();
    if (pipe_pair.first)
        pipes.push_back(pipe_pair.first);
    if (pipe_pair.second)
        pipes.push_back(pipe_pair.second);
}

void Model::move_pipes() {
    if (state != 1)
        return;
    for (auto pipe: pipes)
        pipe->move();
}

void Model::remove_invisible_pipes() {
    if (state != 1)
        return;
    auto new_end = std::remove_if(pipes.begin(), pipes.end(), [](Body* body) {
        if (body->get_x() < -(body->get_width() * 1.5f)) {
            delete body;
            return true;
        }
        return false;
    });
    pipes.erase(new_end, pipes.end());
}

void Model::check_crash() {
    if (state != 1)
        return;
    for (auto pipe: pipes) {
        bool collide = bird->is_collision(*pipe);
        if (collide) {
            crash();
            break;
        }
    }
}

void Model::parse_input(int input) {
    switch (input) {
        case 1: {
            if (state == 1)
                jump();
            else if (state == 0)
                start();
            break;
        }
        case 2: {
            if (state == 2)
                restart();
            break;
        }
    }
}

State Model::update(int input) {
    step++;
    State state;

    drop_bird();
    check_and_fix_position();
    count_score();
    generate_pipes();
    move_pipes();
    remove_invisible_pipes();
    check_crash();
    parse_input(input);

    state.bird = bird->get_state();
    for (auto pipe: pipes)
        state.pipes.push_back(pipe->get_state());
    state.score = score;
    state.high_score = high_score;
    state.is_jump = is_jump();
    state.is_fail = is_fail();
    state.is_pipe_reached = is_pipe_reached();
    state.is_game_over = is_game_over();
    state.step = step;

    return state;
}
