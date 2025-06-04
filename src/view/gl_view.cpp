#include "gl_view.h"
#include "random"
#include "time.h"

bool GL_View::is_alive() {
    if (!window.isOpen())
        return false;

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
    return window.isOpen();
}

int GL_View::get_action() const {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        return 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
        return 2;
    return 0;
}

std::pair<int, int> GL_View::get_size() const {
    return std::make_pair(width, height);
}

std::pair<std::pair<float, float>, std::pair<float, float>> GL_View::get_bird_size() const {
    auto size = std::make_pair(bird_texture[0].getSize().x, bird_texture[0].getSize().y);
    auto scale = std::make_pair(bird.getScale().x, bird.getScale().y);
    return std::make_pair(size, scale);
}

std::pair<std::pair<float, float>, std::pair<float, float>> GL_View::get_pipe_size() const {
    auto size = std::make_pair(pipe_texture.getSize().x, pipe_texture.getSize().y);
    auto scale = std::make_pair(bottom_pipe.getScale().x, bottom_pipe.getScale().y);
    return std::make_pair(size, scale);
}

void GL_View::draw_state(State &state) {
    draw_background();
    draw_bird(state.step, state.is_game_over, state.bird);
    draw_pipes(state.pipes);
    draw_score(state.score, state.high_score);
}

void GL_View::show_state(State &state) {
    draw_state(state);
    sound(state);

    if (state.is_game_over)
        draw_game_over(state.step);

    window.display();
}

GL_View::~GL_View() {
    if (window.isOpen())
        window.close();
}

GL_View::GL_View(int width, int height) : width(width), height(height), tick(1),
    window(sf::VideoMode(width, height), "Flappy Bird", sf::Style::Close)
{
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    std::srand(time(nullptr));

    score_buffer.loadFromFile("./assets/audio/score.wav");
    jump_buffer.loadFromFile("./assets/audio/flap.wav");
    crash_buffer.loadFromFile("./assets/audio/crash.wav");

    score_sound.setBuffer(score_buffer);
    jump_sound.setBuffer(jump_buffer);
    crash_sound.setBuffer(crash_buffer);

    background_texture.loadFromFile("./assets/images/background.png");
    pipe_texture.loadFromFile("./assets/images/pipe.png");
    game_over_texture.loadFromFile("./assets/images/gameover.png");
    bird_texture[0].loadFromFile("./assets/images/flappy1.png");
    bird_texture[1].loadFromFile("./assets/images/flappy1.png");
    bird_texture[2].loadFromFile("./assets/images/flappy2.png");

    bird.setScale(2, 2);

    top_pipe.setTexture(pipe_texture);
    top_pipe.setScale(2, -2);

    bottom_pipe.setTexture(pipe_texture);
    bottom_pipe.setScale(2, 2);

    background[0].setTexture(background_texture);
    background[1].setTexture(background_texture);
    background[2].setTexture(background_texture);
    background[0].setScale(1.15625, 1.171875);
    background[1].setScale(1.15625, 1.171875);
    background[2].setScale(1.15625, 1.171875);
    background[1].setPosition(333, 0);
    background[2].setPosition(666, 0);

    game_over.setTexture(game_over_texture);
    game_over.setOrigin(96, 21);
    game_over.setPosition(500, 125);
    game_over.setScale(2, 2);

    font.loadFromFile("./assets/fonts/flappy.ttf");

    restart_text.setString("Press C to restart");
    restart_text.setFont(font);
    restart_text.setFillColor(sf::Color::White);
    restart_text.setCharacterSize(50);
    restart_text.setOrigin(restart_text.getLocalBounds().width / 2, 0);
    restart_text.setPosition(500, 250);

    score_text.setFont(font);
    score_text.setFillColor(sf::Color::White);
    score_text.setCharacterSize(75);
    score_text.move(30, 0);

    high_score_text.setFont(font);
    high_score_text.setFillColor(sf::Color::White);
    high_score_text.move(30, 80);
}

void GL_View::draw_background() {
    window.clear();
    window.draw(background[0]);
    window.draw(background[1]);
    window.draw(background[2]);
}

void GL_View::sound(State &state) {
    if (state.is_jump && jump_sound.getStatus() != sf::Sound::Status::Playing)
        jump_sound.play();
    if (state.is_pipe_reached)
        score_sound.play();
    if (state.is_fail)
        crash_sound.play();
}

void GL_View::draw_bird(int step, bool game_over, std::map<std::string, float> &data) {
    if (!game_over) {
        if (step % 6 == 0)
            tick += 1;
        if (tick == 3)
            tick = 0;
    }
    bird.setTexture(bird_texture[tick]);
    draw_body(bird, data);
}

void GL_View::draw_pipes(std::vector<std::map<std::string, float>> &data) {
    for (auto pipe: data) {
        auto sprite = pipe["type"] == 1 ? bottom_pipe : top_pipe;
        draw_body(sprite, pipe);
    }
}

void GL_View::draw_body(sf::Sprite &sprite, std::map<std::string, float> &data) {
    auto coordinates = convert_dimensions(data["x"], data["y"]);
    sprite.setPosition(coordinates.first, coordinates.second);
    window.draw(sprite);
}

void GL_View::draw_score(int score, int high_score) {
    score_text.setString(std::to_string(score));
    high_score_text.setString("HI " + std::to_string(high_score));
    window.draw(score_text);
    window.draw(high_score_text);
}

void GL_View::draw_game_over(int step) {
    window.draw(game_over);
    if (step % 60 < 30)
        window.draw(restart_text);
}

std::pair<float, float> GL_View::convert_dimensions(int x, int y) const {
    return std::make_pair(x, height-y);;
}

