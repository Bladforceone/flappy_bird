#ifndef FLAPPY_BIRD_GL_VIEW_H
#define FLAPPY_BIRD_GL_VIEW_H

#include "view.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class GL_View : public View {
public:
    GL_View(int width = 1000, int height = 600);

    bool is_alive();

    int get_action() const;
    std::pair<int, int> get_size() const;
    std::pair<std::pair<float, float>, std::pair<float, float>> get_bird_size() const;
    std::pair<std::pair<float, float>, std::pair<float, float>> get_pipe_size() const;

    void show_state(State &state);

    ~GL_View();
private:
    std::pair<float, float> convert_dimensions(int x, int y) const;

    void draw_state(State &state);
    void sound(State &state);

    void draw_background();
    void draw_bird(int step, bool game_over, std::map<std::string, float>& data);
    void draw_pipes(std::vector<std::map<std::string, float>>& data);
    void draw_body(sf::Sprite& sprite, std::map<std::string, float>& data);
    void draw_score(int score, int high_score);
    void draw_game_over(int step);

    int tick;

    int width;
    int height;

    sf::RenderWindow window;

    sf::SoundBuffer score_buffer;
    sf::SoundBuffer jump_buffer;
    sf::SoundBuffer crash_buffer;

    sf::Sound score_sound;
    sf::Sound jump_sound;
    sf::Sound crash_sound;

    sf::Texture pipe_texture;
    sf::Texture background_texture;
    sf::Texture game_over_texture;
    sf::Texture bird_texture[3];

    sf::Sprite background[3];
    sf::Sprite bird;
    sf::Sprite game_over;
    sf::Sprite top_pipe;
    sf::Sprite bottom_pipe;

    sf::Font font;

    sf::Text restart_text;
    sf::Text score_text;
    sf::Text high_score_text;
};


#endif //FLAPPY_BIRD_GL_VIEW_H
